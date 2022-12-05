#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H


#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "dfsgraph.h"
#include "djalgo.h"
#include "mstalgo.h"
#include "bfsalgo.h"

namespace Ui {
class adminwindow;
}

class adminwindow : public QWidget
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();
    void initStartingTeams(QString fileName);
    void initStartingSouvenirs(QString fileName);
    void initStartingDistances(QString fileName);

    signals:
        void goToMainSelectWindow();
private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();

    void on_initStartingInfoPushButton_clicked();

    void on_pushButton_2_clicked();

    void on_deleteTablesPushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_goBackMenuAdmin2_clicked();

    void on_goBackAdmin3_clicked();


    void on_initNewFilesPushButton_clicked();

    void on_mstOfNFLStadiumsPushButton_clicked();

    void on_bfsFromLaRamsPushButton_clicked();

    void on_nflTeamBermudaGrassPushButton_clicked();

    void on_goBackAdmin4_clicked();

    void on_totalSeatingCapacityPushButton_clicked();

private:
    Ui::adminwindow *ui;
    bool ifSanDiego = false;
};

#endif // ADMINWINDOW_H
