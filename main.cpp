#include "timerform.h"

#include <QApplication>
#include <fstream>

const QString messagePattern = "%{time} [%{type}%{if-debug} function=%{function}, line=%{line}, file=%{file}%{endif}] %{message}";

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    static std::fstream logfile("TomatoTimer.log", std::ios_base::app);
    logfile << qPrintable(qFormatLogMessage(type, context, message)) << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    (void)qInstallMessageHandler(messageHandler);
    qSetMessagePattern(messagePattern);

    TimerForm w;
    w.show();
    const auto result = a.exec();
    qInfo("TomatoTimer exited with %i", result);
    return result;
}
