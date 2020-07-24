#include "tomatosettingsdialog.h"
#include "ui_tomatosettingsdialog.h"

TomatoSettingsDialog::TomatoSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TomatoSettingsDialog)
{
    ui->setupUi(this);
}

TomatoSettingsDialog::~TomatoSettingsDialog()
{
    delete ui;
}
