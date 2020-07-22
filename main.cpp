#include "timerform.h"

#include <QApplication>
#ifdef WIN32
#include <Windows.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef WIN32
#ifdef qDebug
    FreeConsole();
#endif
#endif
    TimerForm w;
    w.show();
    return a.exec();
}
