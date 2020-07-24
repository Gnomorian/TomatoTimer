#include "tomatosettingsdialog.h"
#include "ui_tomatosettingsdialog.h"
#include "tomatoapplication.h"
#include <QCloseEvent>

TomatoSettingsDialog::TomatoSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TomatoSettingsDialog)
{
    ui->setupUi(this);
    setup();
}

TomatoSettingsDialog::~TomatoSettingsDialog()
{
    delete ui;
}

void TomatoSettingsDialog::setup()
{
    const auto app = TomatoApplication::getInstance();
    ui->spinSessionLength->setValue(app->getSessionLength());
    ui->spinShortBreak->setValue(app->getShortBreakLength());
    ui->spinLongBreakMax->setValue(app->getLongBreakMaximumLength());
    ui->spinLongBreakMin->setValue(app->getLongBreakMinimumLength());
    ui->spinLongPrerequisite->setValue(app->getLongBreakPrerequisite());
}

void TomatoSettingsDialog::saveSettings()
{
    const auto app = TomatoApplication::getInstance();
    app->setSessionLength(ui->spinSessionLength->value());
    app->setShortBreakLength(ui->spinShortBreak->value());
    app->setLongBreakMaximumLength(ui->spinLongBreakMax->value());
    app->setLongBreakMinimumLength(ui->spinLongBreakMin->value());
    app->setLongBreakPrerequisite(ui->spinLongPrerequisite->value());
    app->flushSettings();
}

void TomatoSettingsDialog::closeEvent(QCloseEvent* event)
{
    event->accept();
    delete this;
}

void TomatoSettingsDialog::on_btnCancel_clicked()
{
    close();
}

void TomatoSettingsDialog::on_btnSave_clicked()
{
    saveSettings();
    close();
}
