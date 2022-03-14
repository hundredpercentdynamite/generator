#include "mainwindow.h"
#include "media.h"
#include "data.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QMediaPlaylist>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);

  this->settings = new QSettings("Kleymenov", "ical-gen", this);
  loadSettings();
  this->calendar = new Calendar(this->eventDir);
  this->data = new Data(DATA_FILENAME);
  this->api = new ApiClient(BASE);
  QObject::connect(this->api, &ApiClient::dataLoaded, this, [=](QJsonObject& jsonData) {
    this->data->saveData(jsonData);
    this->setComboboxOptions(jsonData);
  });
  if (!this->data->exist()) {
    this->loadDataFromApi();
  } else {
    QJsonObject dataFromFile = this->data->loadData();
    this->setComboboxOptions(dataFromFile);
  }

  QObject::connect(this->api, &ApiClient::scheduleLoaded, this, [=](QJsonObject& jsonData) {
//    qDebug() << "schedule:    " << jsonData["schedule"];
    this->calendar->generateEvents(jsonData);
  });

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
  this->calendar->setEventsDir(e_dir);
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
  this->eventDir = e_dir;
  QString j_dir = settings->value("journal_dir", CURRENT_DIR).toString();
  ui->journalDir->setText(j_dir);
  bool with_jokes = settings->value("with_jokes", true).toBool();
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

void MainWindow::setComboboxOptions(QJsonObject& jsonData) {
  ui->group->addItem("", 0);
  ui->teacher->addItem("", 0);
  QJsonArray groups = jsonData.value("groups").toArray();
  QJsonArray teachers = jsonData.value("teachers").toArray();
  QJsonArray::iterator i;
  for (i = groups.begin(); i != groups.end(); i++) {
    QJsonObject group = i->toObject();
    int groupId = group.value("id").toInt();
    QString groupName = group.value("name").toString();
    ui->group->addItem(groupName, groupId);
  }
  QJsonArray::iterator t;
  for (t = teachers.begin(); t != teachers.end(); t++) {
    QJsonObject teacher = t->toObject();
    int teacherId = teacher.value("id").toInt();
    QString firstName = teacher.value("first_name").toString();
    QString lastName = teacher.value("last_name").toString();
    QString middleName = teacher.value("mid_name").toString();
    QString resultName = lastName + " " + firstName + " " + middleName;
    if (lastName.contains("Вакансия")) {
      continue;
    }
    ui->teacher->addItem(resultName, teacherId);
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


void MainWindow::on_group_activated(int _)
{
  ui->teacher->setCurrentIndex(0);
}

void MainWindow::on_teacher_activated(int _)
{
  ui->group->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
  int groupId = ui->group->currentData().toInt();
  int teacherId = ui->teacher->currentData().toInt();
  QDate currentMonday = QDate::currentDate();
  currentMonday = currentMonday.addDays(Qt::Monday - currentMonday.dayOfWeek());
  QString isoCurrentMonday = currentMonday.toString(Qt::ISODate);

  QDate nextMonday = currentMonday.addDays(7);
  QString isoNextMonday = nextMonday.toString(Qt::ISODate);

  if (groupId) {
    qDebug() << "groupId:  " << groupId;
    this->api->loadScheduleByGroup(groupId, isoCurrentMonday);
    this->api->loadScheduleByGroup(groupId, isoNextMonday);
  } else if (teacherId) {
    qDebug() << "teacherId:   " << teacherId;
    this->api->loadScheduleByTeacher(teacherId, isoCurrentMonday);
    this->api->loadScheduleByTeacher(teacherId, isoNextMonday);
  }
}



