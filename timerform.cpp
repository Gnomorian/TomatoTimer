#include "timerform.h"
#include "ui_timerform.h"
#include <QTime>
#include <QThread>
#include <QSound>

TimerForm::TimerForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TimerForm), focusSessionCount(0), countSinceLastLongRest(0), sessionRunning(false), paused(false)
    , sessionTimer(this), clockUpdateTimer(this)
{
    ui->setupUi(this);

    // by default the text box has focus which hides the placeholder text saying what its for, dont want that.
    ui->btnStart->setFocus();

    setupConnections();
}

TimerForm::~TimerForm()
{
    delete ui;
}

void TimerForm::setupConnections()
{
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(ui->btnLongBreak, SIGNAL(clicked()), this, SLOT(onLongTimerClicked()));
    connect(ui->btnQuickBreak, SIGNAL(clicked()), this, SLOT(onShortTimerClicked()));

    connect(&sessionTimer, SIGNAL(timeout()), this, SLOT(stopSession()));
    connect(&clockUpdateTimer, SIGNAL(timeout()), this, SLOT(onClockUpdate()));
}

void TimerForm::startNewSession()
{
    sessionRunning = true;
    ui->btnStart->setText("Pause");
    ui->btnStart->setToolTip("Pause the current session for some unforseen important thing.");
    ui->btnLongBreak->setEnabled(false);
    ui->btnQuickBreak->setEnabled(false);
    QString task = ui->txtCurrentTask->text();
    if(task.isEmpty())
        ui->statusbar->showMessage(QString("Working for %2 minutes").arg(session_length));
    else
        ui->statusbar->showMessage(QString("Working on %1 for %2 minutes").arg(ui->txtCurrentTask->text()).arg(session_length));
    startSessionTimer(session_length);
}

void TimerForm::pauseSession()
{
    paused = true;
    ui->btnStart->setText("Resume");
    ui->btnStart->setToolTip("Resume the current sesson");
    sessionTimer.stop();
    clockUpdateTimer.stop();
    ui->statusbar->showMessage("Paused session.");
}

void TimerForm::resumeSession()
{
    paused = false;
    ui->btnStart->setText("Pause");
    ui->btnStart->setToolTip("Pause the current session for some unforseen important thing.");
    sessionTimer.start();
    clockUpdateTimer.start();
    ui->statusbar->showMessage("Resumed session.");
}

void TimerForm::stopSession()
{
    sessionRunning = false;
    ui->btnStart->setText("Start");
    ui->btnStart->setToolTip("Start a 25 focus session");
    ++focusSessionCount;

    if(++countSinceLastLongRest >= session_count_for_long_break)
        ui->btnLongBreak->setEnabled(true);
    else
        ui->btnQuickBreak->setEnabled(true);
    QSound::play("rooster.wav");
    ui->statusbar->showMessage(QString("You have completed %1 sessions!").arg(focusSessionCount));
}

void TimerForm::onClockUpdate()
{
    if(sessionTimer.remainingTime() != -1)
    {
        updateClock(sessionTimer.remainingTime());
    }
}

LongRestLength TimerForm::queryLongBreakLength()
{
    QMessageBox messageBox(QMessageBox::Icon::Question, "How long?", "How long would you like your long break to be?");
    const auto shortRest = messageBox.addButton("15 minnutes", static_cast<QMessageBox::ButtonRole>(LongRestLength::Short15));
    const auto longRest = messageBox.addButton("30 minutes", static_cast<QMessageBox::ButtonRole>(LongRestLength::Long30));
    messageBox.setWindowModality(Qt::WindowModality::ApplicationModal);
    messageBox.setModal(true);
    messageBox.exec();
    const auto clicked = messageBox.clickedButton();

    if(clicked == longRest)
        return LongRestLength::Long30;
    if(clicked == shortRest)
        return LongRestLength::Short15;
    return LongRestLength::Canceled;
}

void TimerForm::updateClock(int milliseconds)
{
    const QTime time = QTime(0, 0, 0).addMSecs(milliseconds);
    QString displayTime = QString("%1:%2").arg(time.minute(), 2, 10, QLatin1Char('0')).arg(time.second(), 2, 10, QLatin1Char('0'));
    ui->lblCurrentTime->setText(clockLabelFormat.arg(displayTime));
}

void TimerForm::startSessionTimer(int minutes)
{
    clockUpdateTimer.stop();
    sessionTimer.stop();

    sessionTimer.setInterval(std::chrono::minutes(minutes));
    sessionTimer.setTimerType(Qt::PreciseTimer);
    sessionTimer.setSingleShot(true);
    sessionTimer.start();

    // if we do a timer of 1000, sometimes we dont update the time for 2 seconds.
    clockUpdateTimer.start(200);
    updateClock(0);
}

void TimerForm::onStartClicked()
{
    if(sessionRunning)
        if(paused)
            resumeSession();
        else
            pauseSession();
    else
        startNewSession();
}

void TimerForm::onShortTimerClicked()
{
    startSessionTimer(short_break_length);
}

void TimerForm::onLongTimerClicked()
{
    const auto breakLength = queryLongBreakLength();
    if(breakLength == LongRestLength::Canceled)
        return;
    else if(breakLength == LongRestLength::Long30)
        startSessionTimer(long_break_maximum_length);
    else if(breakLength == LongRestLength::Short15)
        startSessionTimer(long_break_minimum_length);
    countSinceLastLongRest = 0;
}

