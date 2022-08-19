#ifdef WIN32
#   include <Windows.h>
#endif
#include <QDebug>
#include "QVstConsole.h"
#include "QVstApplication.h"

#ifdef WIN32
static HHOOK s_hHook;

LRESULT CALLBACK msgFilterProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (qApp) {
        qApp->sendPostedEvents();
    }
    return CallNextHookEx(s_hHook, nCode, wParam, lParam);
}
#endif

struct QVstApplication::Private
{
    Qt::HANDLE handle;
    QVstConsole *pConsole;
};

static void msgHandler(QtMsgType type, const QMessageLogContext &contect, const QString &text)
{
    QByteArray baText = text.toLatin1();
    switch (type) {
    case QtFatalMsg:
    case QtCriticalMsg:
    case QtWarningMsg:
    case QtDebugMsg:
    default: {
        QVstConsole *pConsole = QVstApplication::instance()->console();
        if (pConsole != nullptr) {
            QVstApplication::instance()->console()->writeLine(baText.constData());
        }
        break;
    }
    }
}

QVstApplication* QVstApplication::createInstance(Qt::HANDLE handle, Flags flags)
{
    QApplication *pGuiApp = qApp;
    if (pGuiApp) {
        return static_cast<QVstApplication*>(pGuiApp);
    }

    int argc = 0;
    QVstApplication *pInstance = new QVstApplication(argc, nullptr, handle, flags);
    if ((flags & Flag_CreateConsole) != 0) {
        // Install log messages handler only if there is a console
        qInstallMessageHandler(msgHandler);
    }

    return pInstance;
}

QVstApplication* QVstApplication::instance()
{
    return static_cast<QVstApplication*>(qApp);
}

QVstApplication::QVstApplication(int &argc, char **argv, Qt::HANDLE handle, Flags flags)
    : QApplication(argc, argv)
{
    m = new Private;
    m->handle = handle;
    m->pConsole = nullptr;
    if ((flags & Flag_CreateConsole) != 0) {
        m->pConsole = new QVstConsole(this);
    }

#ifdef WIN32
    s_hHook = SetWindowsHookEx(WH_GETMESSAGE, msgFilterProc, 0, GetCurrentThreadId());
#endif

    setAttribute(Qt::AA_NativeWindows, true);
}

QVstApplication::~QVstApplication()
{
#ifdef WIN32
    UnhookWindowsHookEx(s_hHook);
#endif
    delete m;
}

QVstConsole* QVstApplication::console() const
{
    return m->pConsole;
}
