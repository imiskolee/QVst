#ifdef WIN32
#   include <Windows.h>
#endif
#include <cstdio>
#include "QVstConsole.h"

#ifdef WIN32
#   define snprintf _snprintf_s
#endif

struct QVstConsole::Private
{
#ifdef WIN32
    HANDLE hConsole;
#endif
};

QVstConsole::QVstConsole(QObject *pParent)
    : QObject(pParent)
{
    m = new Private;
#ifdef WIN32
    AllocConsole();
    //SetConsoleTitle("Console");
    m->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

QVstConsole::~QVstConsole()
{
#ifdef WIN32
    FreeConsole();
#endif
    delete m;
}

void QVstConsole::writeLine(const char *str)
{
    char buf[256] = {0};
    snprintf(buf, 255, "%s\n", str);
#ifdef WIN32
    DWORD written = 0;
    WriteConsole(m->hConsole, buf, static_cast<DWORD>(strlen(buf)), &written, 0);
#endif
}
