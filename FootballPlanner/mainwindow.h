#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_admin_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_main_clicked();

    void on_pushButton_homeAdminEdit_clicked();

    void on_pushButton_homeMainPage_clicked();

    void on_stadiumNamePushButton_clicked();

    void on_nflTeamsPushButton_clicked();

    void on_searchTeamPushBUtton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase myDb;
};
#endif // MAINWINDOW_H
