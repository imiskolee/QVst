#ifndef QVST_CONSOLE_H
#define QVST_CONSOLE_H

#include <QObject>

class QVstConsole : public QObject
{
    Q_OBJECT
public:

    QVstConsole(QObject *pParent = nullptr);
    ~QVstConsole();

    void writeLine(const char *str);

private:

    struct Private;

    Private *m;
};

#endif // QVST_CONSOLE_H
