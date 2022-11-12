#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "mainmenu.h"
#include "menuselectwindow.h"
#include "tripselectwindow.h"
#include "adminwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
        void moveAdminPage();
        void moveMainWindowPage();
        void moveMenuSelectPage();
        void moveMenuSelectPageAdmin();
        void moveTripSelectWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase myDb;
    mainmenu mainMenu;
    adminwindow adminWindow;
    menuselectwindow menuSelectWindow;
    tripselectwindow tripSelectWindow;
};

#endif // MAINWINDOW_H
