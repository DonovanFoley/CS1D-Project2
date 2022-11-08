#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
