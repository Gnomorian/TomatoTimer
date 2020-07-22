#include "timerform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimerForm w;
    w.show();
    return a.exec();
}
