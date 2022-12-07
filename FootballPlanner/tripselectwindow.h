/*****************************************************************//**
 * \file   tripselectwindow.h
 * \brief  ui to allow user to select the type of trip they wish to
 *          go on
 * 
 * \date   December 2022
 *********************************************************************/

#ifndef TRIPSELECTWINDOW_H
#define TRIPSELECTWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class tripselectwindow;
}


class tripselectwindow : public QWidget
{
    Q_OBJECT

public:
    explicit tripselectwindow(QWidget *parent = nullptr);
    ~tripselectwindow();

    signals:
        void goToMainSelectWindow();
private slots:
    void on_mainMenuPushButton_clicked();

    void on_OrderPushButton_clicked();

    void on_addOrderTeamPushButton_clicked();

    void on_calcDistancePushButton_clicked();

    void on_DJPushButton_clicked();

    void on_DJSelectPushButton_clicked();

    void on_CustomPushButton_clicked();

    void on_addCustomTeamPushButton_clicked();

    void on_calcCustomDistancePushButton_clicked();

    void on_BeginTripPushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_addSouvenirButton_clicked();

    void on_endTripPushButton_clicked();

    void on_customTripBeginFastestPushButton_clicked();

    void on_goBackPushButton_clicked();

    void on_PatriotsPushButton_clicked();

    void on_AllTeamBeginPushButton_clicked();

    void on_pushButton_clicked();

    void on_DJBeginTripButton_clicked();

private:
    Ui::tripselectwindow *ui;

    QSqlDatabase myDb;
    QSqlQueryModel *queryModel;
    QSqlQueryModel *queryModel2;

    int count = 1;
    int addTeam = 0;
    int nextTeamCheck;
    bool notClicked = true;
    //bool parisNotClicked = true;
    //bool customTripNotClicked = true;
};

#endif // TRIPSELECTWINDOW_H
