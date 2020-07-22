#ifndef TIMERFORM_H
#define TIMERFORM_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class TimerForm; }
QT_END_NAMESPACE

enum LongRestLength
{
    Short15 = QMessageBox::ButtonRole::NoRole,
    Long30 = QMessageBox::ButtonRole::YesRole
};

class TimerForm : public QMainWindow
{
    Q_OBJECT
    const int session_length = 25;
    const int short_break_length = 5;
    const int long_break_minimum_length = 15;
    const int long_break_maximum_length = 30;
    const int session_count_for_long_break = 4;
    const QString clockLabelFormat = "<b style=\"font-size:30pt\">%1</b>";
public:
    TimerForm(QWidget *parent = nullptr);
    ~TimerForm();
protected:
    void setupConnections();

    void startNewSession();
    void pauseSession();
    void resumeSession();
    void doShortBreak();
    void doLongBreak();
    LongRestLength queryLongBreakLength();
    void updateClock(int milliseconds);

    void startSessionTimer(int minutes);
protected slots:
    void onStartClicked();
    void onShortTimerClicked();
    void onLongTimerClicked();
    void onClockUpdate();
    void stopSession();
private:
    Ui::TimerForm *ui;
    int focusSessionCount;
    bool sessionRunning;
    bool paused;
    QTimer sessionTimer;
    QTimer clockUpdateTimer;
};
#endif // TIMERFORM_H
