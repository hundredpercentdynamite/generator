#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apiclient.h"
#include "files.h"
#include <QMainWindow>
#include <QSettings>
#include <QString>
#include <QDir>
#include <QMovie>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

  ~MainWindow();

  void saveSettings();

  void loadSettings();

  void loadDataFromApi();

  void playAllMedia();

  void stopAllMedia();

  void checkAndPlayAllMedia();

  void setComboboxOptions(QJsonObject& data);

private slots:

  void on_goToSettings_clicked();

  void on_goBackButton_clicked();

  void on_chooseEventDir_clicked();

  void on_chooseJournalDir_clicked();

  void on_saveSettings_clicked();

  void on_refreshData_clicked();

  void on_pushButton_clicked();

  void on_teacher_activated(int index);

  void on_group_activated(int index);

private:
  Ui::MainWindow *ui;
  QSettings *settings;
  ApiClient *api;
  Files *files;
  const int FILIAL_ID = 880;
  QString BASE;
  const QString DEFAULT_API = "https://login.misis.ru/";
  const QString CURRENT_DIR = QDir::currentPath();
  const QString DATA_FILENAME = "data.json";
  const QString MAIN_BG_PATH = ":/mainBg.gif";
  const QString SETTINGS_BG_PATH = ":/settingsBg.gif";
  const QString MUSIC_PATH = "qrc:/music.mp3";

  QMovie *mainBgImg;
  QMovie *settingsBgImg;
  QMediaPlayer *music;
};

#endif // MAINWINDOW_H
