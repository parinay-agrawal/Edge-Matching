#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(1);
    this->setWindowTitle("set grid size");
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    N = ui->spinBox->value();
}

int SettingsDialog::getN()
{
   return N;
}

void SettingsDialog::setN(int n)
{
    if (n>0) {
        N = n;
        ui->spinBox->setValue(N);
    }
}

void SettingsDialog::on_buttonBox_rejected()
{
    ui->spinBox->setValue(N);
}
