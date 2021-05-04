#ifndef TIMERFORM_H
#define TIMERFORM_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class TimerForm; }
QT_END_NAMESPACE

/*!
 * \brief The LongRestLength enum
 * \list
 * \li Canceled - closed the form without pressing something\n
 * \li Short15 - user requested a 15 minute long rest
 * \li Long30 - user requested a 30 minute long rest
 * \endlist
 */
enum LongRestLength
{
    Canceled,
    Short15 = QMessageBox::ButtonRole::NoRole,
    Long30 = QMessageBox::ButtonRole::YesRole
};

enum SessionType
{
    Undefined,
    LongRest,
    ShortRest,
    Focus
};

class TimerForm : public QMainWindow
{
    Q_OBJECT
    const QString clockLabelFormat = "<b style=\"font-size:30pt\">%1</b>";
public:
    TimerForm(QWidget *parent = nullptr);
    ~TimerForm();
protected:
    void setupConnections();

    void doFocusSession();
    void pauseSession();
    void resumeSession();
    void doShortBreak();
    void doLongBreak();
    LongRestLength queryLongBreakLength();
    void updateClock(int milliseconds);
    bool lastSessionWasBreak() const;

    void startSessionTimer(int minutes);
protected slots:
    void onStartClicked();
    void onShortTimerClicked();
    void onLongTimerClicked();
    void onClockUpdate();
    void stopSession();
    void onSettings();
private:
    Ui::TimerForm *ui{nullptr};
    int focusSessionCount{0};
    int countSinceLastLongRest{0};
    bool sessionRunning{false};
    bool paused{false};
    SessionType lastSessionType{SessionType::Undefined};
    QTimer sessionTimer;
    QTimer clockUpdateTimer;
};
#endif // TIMERFORM_H
