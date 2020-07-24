#ifndef TOMATOSETTINGSDIALOG_H
#define TOMATOSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class TomatoSettingsDialog;
}

class TomatoSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TomatoSettingsDialog(QWidget *parent = nullptr);
    ~TomatoSettingsDialog();

private:
    Ui::TomatoSettingsDialog *ui;
};

#endif // TOMATOSETTINGSDIALOG_H
