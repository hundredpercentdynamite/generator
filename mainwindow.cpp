#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    this->settings = new QSettings("Kleymenov", "ical-gen", this);
    loadSettings();

    this->api = new ApiClient(this->BASE);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::saveSettings()
{
    QString apipath = ui->apiPath->text();
    settings->setValue("api_path", apipath);
    QString e_dir = ui->eventDir->text();
    settings->setValue("event_dir", e_dir);
    QString j_dir = ui->journalDir->text();
    settings->setValue("journal_dir", j_dir);
}

void MainWindow::loadSettings()
{
    QString apipath = settings->value("api_path", this->DEFAULT_API).toString();
    ui->apiPath->setText(apipath);
    this->BASE = apipath;
    QString e_dir = settings->value("event_dir", this->CURRENT_DIR).toString();
    ui->eventDir->setText(e_dir);
    QString j_dir = settings->value("journal_dir", this->CURRENT_DIR).toString();
    ui->journalDir->setText(j_dir);
}


void MainWindow::on_goToSettings_clicked()
{
    this->loadSettings();
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_goBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_chooseEventDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->eventDir->setText(dir);
}


void MainWindow::on_chooseJournalDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->journalDir->setText(dir);
}


void MainWindow::on_saveSettings_clicked()
{
    this->saveSettings();
}


void MainWindow::on_refreshData_clicked()
{
    this->api->loadGroups(this->FILIAL_ID);
}

