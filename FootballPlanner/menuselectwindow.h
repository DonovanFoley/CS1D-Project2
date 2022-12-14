/*****************************************************************//**
 * \file   menuselectwindow.h
 * \brief  ui that allows user to display information about the
 *          teams
 * 
 * \author Admin
 * \date   December 2022
 *********************************************************************/

#ifndef MENUSELECTWINDOW_H
#define MENUSELECTWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "mapsouvenir.h"

namespace Ui {
class menuselectwindow;
}

class menuselectwindow : public QWidget
{
    Q_OBJECT

public:
    explicit menuselectwindow(QWidget *parent = nullptr);
    ~menuselectwindow();

       signals:
            void goToCustomTripPage();
            void goBackToMenu();
private slots:
    void on_nflTeamsPushButton_clicked();

    void on_customTripPushButton_clicked();

    void on_pushButton_clicked();

    void on_stadiumNamesAndTeamsPushButton_clicked();

    void on_nflSearchPushButton_clicked();

    void on_searchPushButton_clicked();

    void on_goBackSecondPushButton_clicked();

    void on_stadiumsByDatePushButton_clicked();

    void on_afcTeamPushButton_clicked();

    void on_nfcTeamsPushButton_clicked();

    void on_nfcNorthPushButton_clicked();

    void on_nflTeamSouvenir_clicked();

    void on_souvenirSearchButton_clicked();

    void on_goBackSecondPushButton_2_clicked();

    void on_openRoofStadiumInfo_clicked();

    void on_nflSeatingCapacity_clicked();

    void on_conferenceSort_clicked();

    void on_mainWindowButton_clicked();

private:
    Ui::menuselectwindow *ui;
    QSqlDatabase myDb;

};

#endif // MENUSELECTWINDOW_H
