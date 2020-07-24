#ifndef TOMATOAPPLICATION_H
#define TOMATOAPPLICATION_H

#include <QApplication>
#include <QSettings>

const static int default_session_length = 25;
const static int default_short_break_length = 5;
const static int default_long_break_minimum_length = 15;
const static int default_long_break_maximum_length = 30;
const static int default_long_break_prerequisite = 4;

class TomatoApplication : public QApplication
{
    Q_OBJECT
    const QString TimerGroup = "TimerDurations";
    const QString ConditionGroup = "Conditions";
    const QString SessionLength = "session_length";
    const QString ShortBreakLength = "short_break_length";
    const QString LongBreakMinimum = "long_break_min";
    const QString LongBreakMaximum = "long_break_max";
    const QString LongBreakPrerequisite = "long_break_prerequisite";

    static TomatoApplication* instance;
    static int session_length;
    static int short_break_length;
    static int long_break_minimum_length;
    static int long_break_maximum_length;
    static int long_break_prerequisite;

    const QString messagePattern = "%{time} [%{type}%{if-debug} function=%{function}, line=%{line}, file=%{file}%{endif}] %{message}";
    QSettings* settings;
public:
    explicit TomatoApplication(int argc, char* argv[]);
    static int exec();
    static TomatoApplication* getInstance();
    void setSessionLength(int minutes);
    void setShortBreakLength(int minutes);
    void setLongBreakMinimumLength(int minutes);
    void setLongBreakMaximumLength(int minutes);
    void setLongBreakPrerequisite(int minutes);
    int getSessionLength();
    int getShortBreakLength();
    int getLongBreakMinimumLength();
    int getLongBreakMaximumLength();
    int getLongBreakPrerequisite();
    void flushSettings();
protected:
    void setupLogging();
    void setupSettings();
    static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message);
signals:

};

#endif // TOMATOAPPLICATION_H
