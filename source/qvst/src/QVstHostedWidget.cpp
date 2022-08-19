#include <QDebug>
#include <QEvent>
#include <QChildEvent>
#include <QFocusEvent>
#include <QPaintEvent>
#include "QVstApplication.h"
#include "QVstHostedWidget.h"
#include <iostream>
using namespace std;
struct QVstHostedWidget::Private
{
    HWND hParentWnd;
    bool reenableParent;
    HWND hPrevFocus;
};

QVstHostedWidget::QVstHostedWidget(HWND hParentWnd, QObject *pParent, Qt::WindowFlags f)
    : QWidget(0, f)
{
    std::cout << "QVstHostedWidget::QVstHostedWidget constructor" << std::endl;
    m = new Private;
    if (pParent != nullptr) {
        QObject::setParent(pParent);
    }

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_NativeWindow, true);

    m->hParentWnd = hParentWnd;
    m->reenableParent = false;
    m->hPrevFocus = 0;

    initialize();
}

QVstHostedWidget::~QVstHostedWidget()
{
    delete m;
}

void QVstHostedWidget::setVisible(bool visible)
{
    if (visible) {
        saveFocus();
    }
    QWidget::setVisible(visible);
}

void QVstHostedWidget::adjustSize(const QSize &size)
{
    if (m->hParentWnd) {
        RECT rcParent;
        ::GetWindowRect(m->hParentWnd, &rcParent);

        HWND hWnd = reinterpret_cast<HWND>(winId());
        ::SetWindowPos(hWnd, HWND_TOP, 0, 0, size.width(), size.height(), SWP_SHOWWINDOW);
        move(0, 0);
        resize(size);
        update();
    }
}

void QVstHostedWidget::initialize()
{
    if (m->hParentWnd) {
        HWND hWnd = reinterpret_cast<HWND>(winId());

        RECT rcParent;
        ::GetWindowRect(m->hParentWnd, &rcParent);
        int width = rcParent.right - rcParent.left;
        int height = rcParent.bottom - rcParent.top;

        ::SetWindowLong(hWnd, GWL_STYLE, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
        ::SetParent(hWnd, m->hParentWnd);
        ::SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW);
        ::ShowWindow(hWnd, SW_SHOW);

        // Make the widget visible
        setVisible(true);

        QEvent evt(QEvent::EmbeddingControl);
        QVstApplication::sendEvent(this, &evt);
    }
}

void QVstHostedWidget::saveFocus()
{
    if (!m->hPrevFocus) {
        m->hPrevFocus = ::GetFocus();
    }
    if (!m->hPrevFocus) {
        m->hPrevFocus = m->hParentWnd;
    }
}

void QVstHostedWidget::resetFocus()
{
    if (m->hPrevFocus) {
        ::SetFocus(m->hPrevFocus);
    } else {
        ::SetFocus(m->hParentWnd);
    }
}
