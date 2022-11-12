#ifndef MENUSELECTWINDOW_H
#define MENUSELECTWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

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
private slots:
    void on_nflTeamsPushButton_clicked();

    void on_customTripPushButton_clicked();

    void on_pushButton_clicked();

    void on_stadiumNamesAndTeamsPushButton_clicked();

    void on_nflSearchPushButton_clicked();

    void on_searchPushButton_clicked();

    void on_goBackSecondPushButton_clicked();

private:
    Ui::menuselectwindow *ui;
    QSqlDatabase myDb;

};

#endif // MENUSELECTWINDOW_H
