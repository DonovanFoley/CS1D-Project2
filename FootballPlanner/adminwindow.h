#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H


#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "dfsgraph.h"

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

private:
    Ui::adminwindow *ui;
};

#endif // ADMINWINDOW_H
