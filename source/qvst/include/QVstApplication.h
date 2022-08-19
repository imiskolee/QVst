#ifndef QVSTAPPLICATION_H
#define QVSTAPPLICATION_H

#include <QApplication>
#include <QVstConsole.h>

class QVstApplication : public QApplication
{
    Q_OBJECT
public:

    enum Flags {
        Flag_None = 0,
        Flag_CreateConsole = 1
    };

    static QVstApplication* createInstance(Qt::HANDLE handle, Flags flags = Flag_None);
    static QVstApplication* instance();

    ~QVstApplication();

    QVstConsole* console() const;

private:

    struct Private;

    QVstApplication(int &argc, char **argv, Qt::HANDLE handle, Flags flags = Flag_None);

    Private *m;
};

#endif // QVSTAPPLICATION_H

