#ifndef TOMATOSETTINGSDIALOG_H
#define TOMATOSETTINGSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class TomatoSettingsDialog;
}
QT_END_NAMESPACE

class TomatoSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TomatoSettingsDialog(QWidget *parent = nullptr);
    ~TomatoSettingsDialog();
    void setup();
    void saveSettings();
protected:
    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_btnCancel_clicked();
    void on_btnSave_clicked();
private:
    Ui::TomatoSettingsDialog *ui;
};

#endif // TOMATOSETTINGSDIALOG_H
