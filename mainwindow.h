#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apiclient.h"
#include <QMainWindow>
#include <QSettings>
#include <QString>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveSettings();
    void loadSettings();

private slots:
    void on_goToSettings_clicked();

    void on_goBackButton_clicked();


    void on_chooseEventDir_clicked();

    void on_chooseJournalDir_clicked();

    void on_saveSettings_clicked();

    void on_refreshData_clicked();

private:
    Ui::MainWindow *ui;
    QSettings* settings;
//    ApiClient* api;
    const int FILIAL_ID = 880;
    QString BASE;
    const QString DEFAULT_API = "https://login.misis.ru/";
    const QString CURRENT_DIR = QDir::currentPath();
};
#endif // MAINWINDOW_H
