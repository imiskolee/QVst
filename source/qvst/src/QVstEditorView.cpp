#ifdef WIN32
#   include <Windows.h>
#endif
#include <QDebug>
#include <QLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include "QVstApplication.h"
#include "QVstHostedWidget.h"
#include "QVstParameterContainer.h"
#include "QVstEditorView.h"
#include <iostream>
QVstEditorView::QVstEditorView(Steinberg::Vst::EditController *pController, Steinberg::ViewRect *size)
    : Steinberg::Vst::EditorView(pController, size),
      m_pHostedWidget(nullptr)
{
    m_pParameterContainer = new QVstParameterContainer(pController);
}

QVstEditorView::~QVstEditorView()
{
    delete m_pHostedWidget;
    delete m_pParameterContainer;
}

Steinberg::tresult PLUGIN_API QVstEditorView::isPlatformTypeSupported(Steinberg::FIDString type)
{
    return Steinberg::kResultTrue;
}

Steinberg::tresult PLUGIN_API QVstEditorView::attached(void *parent, Steinberg::FIDString type)
{
    std::cout << "QVstEditorView::attached" << std::endl;
    m_pHostedWidget = new QVstHostedWidget(reinterpret_cast<HWND>(parent));
    QLayout *pLayout = createLayout();
    if (pLayout != nullptr) {
        m_pHostedWidget->setLayout(pLayout);
        m_pHostedWidget->updateGeometry();
    }
    return Steinberg::Vst::EditorView::attached(parent, type);
}

Steinberg::tresult PLUGIN_API QVstEditorView::removed()
{
    std::cout << "QVstEditorView::removed" << std::endl;
    delete m_pHostedWidget;
    m_pHostedWidget = nullptr;
    return Steinberg::kResultOk;
}

Steinberg::tresult PLUGIN_API QVstEditorView::canResize()
{
    //return m_pHostedWidget->canResize();
    return Steinberg::kResultOk;
}

Steinberg::tresult PLUGIN_API QVstEditorView::getSize(Steinberg::ViewRect *size)
{
    if (size == nullptr || m_pHostedWidget == nullptr) {
        return Steinberg::kResultFalse;
    }

    const QRect &rect = m_pHostedWidget->geometry();
    size->top = rect.top();
    size->bottom = rect.bottom();
    size->left = rect.left();
    size->right = rect.right();

    return Steinberg::kResultOk;
}

Steinberg::tresult PLUGIN_API QVstEditorView::onSize(Steinberg::ViewRect *size)
{
    std::cout << "QVstEditorView::onSize" << std::endl;
    if(m_pHostedWidget != nullptr) {
m_pHostedWidget->
adjustSize(QSize(size->getWidth(), size->getHeight())
);
}
    return Steinberg::kResultOk;
}

Steinberg::tresult PLUGIN_API QVstEditorView::checkSizeConstraint(Steinberg::ViewRect* rect)
{
    if (rect == nullptr || m_pHostedWidget == nullptr) {
        return Steinberg::kResultFalse;
    }

    if (rect->getWidth() < m_pHostedWidget->minimumWidth()) {
        rect->right = rect->left + m_pHostedWidget->minimumWidth();
    }
    if (rect->getWidth() > m_pHostedWidget->maximumWidth()) {
        rect->right = rect->left + m_pHostedWidget->maximumWidth();
    }
    if (rect->getHeight() < m_pHostedWidget->minimumHeight()) {
        rect->bottom = rect->top + m_pHostedWidget->minimumHeight();
    }
    if (rect->getHeight() > m_pHostedWidget->maximumHeight()) {
        rect->bottom = rect->top + m_pHostedWidget->maximumHeight();
    }

    return Steinberg::kResultOk;
}

/*
Steinberg::tresult PLUGIN_API QVstEditorView::onKeyDown (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
{
    if (m_pHostedWidget == nullptr
            || !m_pHostedWidget->isActiveWindow()) {
        return Steinberg::kResultFalse;
    }

    QWidget *pReceiver = m_pHostedWidget->focusWidget();
    if (pReceiver == nullptr) {
        pReceiver = m_pHostedWidget;
    }

    QKeyEvent *pEvent = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, QChar(key));
    QVstApplication::postEvent(pReceiver, pEvent);

    return Steinberg::kResultTrue;
}

Steinberg::tresult PLUGIN_API QVstEditorView::onKeyUp (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers)
{
    if (m_pHostedWidget == nullptr
            || !m_pHostedWidget->isActiveWindow()) {
        return Steinberg::kResultFalse;
    }

    QWidget *pReceiver = m_pHostedWidget->focusWidget();
    if (pReceiver == nullptr) {
        pReceiver = m_pHostedWidget;
    }

    //QKeyEvent evt(QEvent::KeyRelease, key, kbdMod);
    QKeyEvent *pEvent = new QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier, QChar(key));
    QVstApplication::postEvent(pReceiver, pEvent);

    return Steinberg::kResultTrue;
}
*/

QWidget* QVstEditorView::centralWidget() const
{
    return m_pHostedWidget;
}

QLayout* QVstEditorView::createLayout()
{
    // By default no GUI layout is created

    return nullptr;
}
