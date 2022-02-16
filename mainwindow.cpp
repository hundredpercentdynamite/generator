#include "mainwindow.h"
#include "media.h"
#include "files.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QMediaPlaylist>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);

  this->settings = new QSettings("Kleymenov", "ical-gen", this);
  loadSettings();

  this->files = new Files(DATA_FILENAME);
  this->api = new ApiClient(BASE);
  QObject::connect(this->api, &ApiClient::dataLoaded, this, [=](QJsonObject& data) {
    this->files->saveData(data);
  });
  if (!this->files->exist()) {
    this->loadDataFromApi();
  }

  QLabel *mainBg = ui->mainBg;
  this->mainBgImg = Media::getBackground(mainBg, MAIN_BG_PATH);

  QLabel *settingsBg = ui->settingsBg;
  this->settingsBgImg = Media::getBackground(settingsBg, SETTINGS_BG_PATH);

  this->music = Media::getMusic(MUSIC_PATH);

}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::saveSettings() {
  QString apipath = ui->apiPath->text();
  settings->setValue("api_path", apipath);
  QString e_dir = ui->eventDir->text();
  settings->setValue("event_dir", e_dir);
  QString j_dir = ui->journalDir->text();
  settings->setValue("journal_dir", j_dir);
  bool with_jokes = ui->jokesCheckbox->isChecked();
  settings->setValue("with_jokes", with_jokes);
}

void MainWindow::loadSettings() {
  QString apipath = settings->value("api_path", DEFAULT_API).toString();
  ui->apiPath->setText(apipath);
  this->BASE = apipath;
  QString e_dir = settings->value("event_dir", CURRENT_DIR).toString();
  ui->eventDir->setText(e_dir);
  QString j_dir = settings->value("journal_dir", CURRENT_DIR).toString();
  ui->journalDir->setText(j_dir);
  bool with_jokes = settings->value("with_jokes", true).toBool();
  qDebug() << "with jokes" << with_jokes;
  ui->jokesCheckbox->setChecked(with_jokes);
}

void MainWindow::loadDataFromApi() {
  this->api->loadData(FILIAL_ID);
}

void MainWindow::playAllMedia() {
  this->mainBgImg->start();
  ui->mainBg->setMovie(this->mainBgImg);
  this->settingsBgImg->start();
  ui->settingsBg->setMovie(this->settingsBgImg);
  this->music->play();
}

void MainWindow::stopAllMedia() {
  this->mainBgImg->stop();
  ui->mainBg->setMovie(nullptr);
  this->settingsBgImg->stop();
  ui->settingsBg->setMovie(nullptr);
  this->music->pause();
}

void MainWindow::checkAndPlayAllMedia() {
  if (this->settings->value("with_jokes", true).toBool()) {
    this->playAllMedia();
  } else {
    this->stopAllMedia();
  }
}


void MainWindow::on_goToSettings_clicked() {
  this->loadSettings();
  ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_goBackButton_clicked() {
  ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_chooseEventDir_clicked() {
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                  QDir::homePath(),
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);
  ui->eventDir->setText(dir);
}


void MainWindow::on_chooseJournalDir_clicked() {
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                  QDir::homePath(),
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);
  ui->journalDir->setText(dir);
}


void MainWindow::on_saveSettings_clicked() {
  this->saveSettings();
  this->checkAndPlayAllMedia();
}


void MainWindow::on_refreshData_clicked() {
  this->loadDataFromApi();
}

