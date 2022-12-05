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
