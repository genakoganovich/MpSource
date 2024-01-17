#include <QSettings>
#include <QFileDialog>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QSettings settings("Gennadiy Koganovich", "Seisee");
    QString str = settings.value("/Settings/template_path", "").toString();
    ui->txtTemplate->setText(str);
    str = settings.value("/Settings/project_info_path", "").toString();
    ui->txtProjectInfo->setText(str);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_cmdTemplate_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.xml");
    QSettings settings("Gennadiy Koganovich", "Seisee");
    settings.setValue("/Settings/template_path", str);
    ui->txtTemplate->setText(str);
}


void SettingsDialog::on_cmdProjectInfo_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.xml");
    QSettings settings("Gennadiy Koganovich", "Seisee");
    settings.setValue("/Settings/project_info_path", str);
    ui->txtProjectInfo->setText(str);
}

