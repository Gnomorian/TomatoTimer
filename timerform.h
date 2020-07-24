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

class TimerForm : public QMainWindow
{
    Q_OBJECT
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
    int countSinceLastLongRest;
    bool sessionRunning;
    bool paused;
    QTimer sessionTimer;
    QTimer clockUpdateTimer;
};
#endif // TIMERFORM_H
