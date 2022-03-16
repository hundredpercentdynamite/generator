#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/ApiClient/apiclient.h"
#include "src/Data/data.h"
#include "src/Calendar/calendar.h"
#include "src/Logger/logger.h"
#include <QMainWindow>
#include <QSettings>
#include <QString>
#include <QDir>
#include <QMovie>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QErrorMessage>
#include <QtMessageHandler>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

private:
  Ui::MainWindow *ui;
  QSettings *settings;
  ApiClient *api;
  Data *data;
  Calendar *calendar;
  const int FILIAL_ID = 880;
  QString BASE;
  const QString DEFAULT_API = "https://login.misis.ru/";
  const QString CURRENT_DIR = QDir::currentPath();
  const QString DATA_FILENAME = "data.json";
  const QString MAIN_BG_PATH = ":/static/mainBg.gif";
  const QString SETTINGS_BG_PATH = ":/static/settingsBg.gif";
  const QString MUSIC_PATH = "qrc:/static/music.mp3";
  QString eventDir;
  QString logDir;
  QMessageBox *loadingModal;
  QMessageBox *helpModal;
  QErrorMessage *errorModal;

  QMovie *mainBgImg;
  QMovie *settingsBgImg;
  QMediaPlayer *music;
public:
  MainWindow(QWidget *parent = nullptr);

  ~MainWindow();

  void saveSettings();

  void loadSettings();

  void loadDefaultSettings();

  void loadDataFromApi();

  void playAllMedia();

  void stopAllMedia();

  void checkAndPlayAllMedia();

  void setComboboxOptions(QJsonObject& jsonData);

  void setModals();

private slots:

  void on_goToSettings_clicked();

  void on_goBackButton_clicked();

  void on_chooseEventDir_clicked();

  void on_chooseJournalDir_clicked();

  void on_saveSettings_clicked();

  void on_defaultButton_clicked();

  void on_refreshData_clicked();

  void on_pushButton_clicked();

  void on_teacher_activated(int index);

  void on_group_activated(int index);

  void handle_data_loaded(QJsonObject& jsonData);

  void handle_schedule_loaded(QJsonObject& jsonData);

  void handle_error(QString& error);

  void on_helpButton_clicked();
};

#endif // MAINWINDOW_H
