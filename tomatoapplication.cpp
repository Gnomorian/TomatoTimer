#include "tomatoapplication.h"
#include "timerform.h"
#include <fstream>

TomatoApplication* TomatoApplication::instance = nullptr;

int TomatoApplication::session_length = default_session_length;
int TomatoApplication::short_break_length = default_short_break_length;
int TomatoApplication::long_break_minimum_length = default_long_break_minimum_length;
int TomatoApplication::long_break_maximum_length = default_long_break_maximum_length;
int TomatoApplication::long_break_prerequisite = default_long_break_prerequisite;

TomatoApplication::TomatoApplication(int argc, char* argv[]) : QApplication(argc, argv), settings(nullptr)
{
    if(TomatoApplication::instance  != nullptr)
    {
        qCritical("an instance of TomatoApplication already existed...");
        abort();
    }
    TomatoApplication::instance = this;

    QCoreApplication::setOrganizationName(APP_ORGANISATION_NAME);
    QCoreApplication::setOrganizationDomain(APP_ORGANISATION_NAME);
    QCoreApplication::setApplicationName(APP_NAME);
    setupLogging();
    setupSettings();
}

int TomatoApplication::exec()
{
    TimerForm form;
    form.show();
    return QGuiApplication::exec();
}

TomatoApplication *TomatoApplication::getInstance()
{
    return TomatoApplication::instance;
}

void TomatoApplication::setSessionLength(int minutes)
{
    settings->beginGroup(TimerGroup);
    settings->setValue(SessionLength, minutes);
    settings->endGroup();
}

void TomatoApplication::setShortBreakLength(int minutes)
{
    settings->beginGroup(TimerGroup);
    settings->setValue(ShortBreakLength, minutes);
    settings->endGroup();
}

void TomatoApplication::setLongBreakMinimumLength(int minimumMinutes)
{
    settings->beginGroup(TimerGroup);
    settings->setValue(LongBreakMinimum, minimumMinutes);
    settings->endGroup();
}

void TomatoApplication::setLongBreakMaximumLength(int maximumMinutes)
{
    settings->beginGroup(TimerGroup);
    settings->setValue(LongBreakMaximum, maximumMinutes);
    settings->endGroup();
}

void TomatoApplication::setLongBreakPrerequisite(int minutes)
{
    settings->beginGroup(ConditionGroup);
    settings->setValue(LongBreakPrerequisite, minutes);
    settings->endGroup();
}

int TomatoApplication::getSessionLength()
{
    settings->beginGroup(TimerGroup);
    session_length = settings->value(SessionLength, default_session_length).toInt();
    settings->endGroup();
    return session_length;
}

int TomatoApplication::getShortBreakLength()
{
    settings->beginGroup(TimerGroup);
    short_break_length = settings->value(SessionLength, default_short_break_length).toInt();
    settings->endGroup();
    return short_break_length;
}

int TomatoApplication::getLongBreakMinimumLength()
{
    settings->beginGroup(TimerGroup);
    long_break_minimum_length = settings->value(SessionLength, default_long_break_minimum_length).toInt();
    settings->endGroup();
    return long_break_minimum_length;
}

int TomatoApplication::getLongBreakMaximumLength()
{
    settings->beginGroup(TimerGroup);
    long_break_maximum_length = settings->value(SessionLength, default_long_break_maximum_length).toInt();
    settings->endGroup();
    return long_break_maximum_length;
}

int TomatoApplication::getLongBreakPrerequisite()
{
    settings->beginGroup(ConditionGroup);
    long_break_prerequisite = settings->value(SessionLength, default_long_break_prerequisite).toInt();
    settings->endGroup();
    return long_break_prerequisite;
}

void TomatoApplication::flushSettings()
{
    settings->sync();
}

void TomatoApplication::setupLogging()
{
    (void)qInstallMessageHandler(TomatoApplication::messageHandler);
    qSetMessagePattern(messagePattern);
}

void TomatoApplication::setupSettings()
{
    QSettings::setDefaultFormat(QSettings::Format::IniFormat);
    instance->settings = new QSettings;

}

void TomatoApplication::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    static std::fstream logfile("TomatoTimer.log", std::ios_base::app);
    logfile << qPrintable(qFormatLogMessage(type, context, message)) << std::endl;
}
