#include "mainwindow.h"
#include "media.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QMovie>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    this->settings = new QSettings("Kleymenov", "ical-gen", this);
    loadSettings();

    this->api = new ApiClient(this->BASE);
    QObject::connect(this->api, &ApiClient::dataLoaded, this, [=]() {
        QJsonValue groups = this->api->data.value("groups");
        QJsonValue teachers = this->api->data.value("teachers");
        qDebug() << "hello!";
    });

    QLabel* mainBg = ui->mainBg;
//    QMovie* mainBgImg = new QMovie(":/mainBg.gif");
//    this->mainBgImg = mainBgImg;
//    mainBg->setMovie(mainBgImg);
//    mainBgImg->start();
//    mainBg->setScaledContents(true);

    QString mainBgPath(":/mainBg.gif");
    this->mainBgImg = Media::getBackground(mainBg, mainBgPath);


    QLabel* settingsBg = ui->settingsBg;
//    QMovie* settingsBgImg = new QMovie(":/settingsBg.gif");
//    this->settingsBgImg = settingsBgImg;
//    settingsBg->setMovie(settingsBgImg);
//    settingsBg->setScaledContents(true);

    QString settingsBgPath(":/settingsBg.gif");
    this->settingsBgImg = Media::getBackground(settingsBg, settingsBgPath);

//    QMediaPlaylist *playlist = new QMediaPlaylist();
//    playlist->addMedia(QUrl("qrc:/music.mp3"));
//    playlist->setPlaybackMode(QMediaPlaylist::Loop);

//    QMediaPlayer *music = new QMediaPlayer();
//    this->music = music;
//    music->setPlaylist(playlist);
//    music->play();

    this->music = Media::getMusic();
    this->music->play();
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
    this->mainBgImg->stop();
    this->settingsBgImg->start();
}


void MainWindow::on_goBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->mainBgImg->start();
    this->settingsBgImg->stop();
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
    this->api->loadData(this->FILIAL_ID);
}

