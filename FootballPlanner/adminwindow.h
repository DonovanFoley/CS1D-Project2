#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H


#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class adminwindow;
}

class adminwindow : public QWidget
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();

    signals:
        void goToMainSelectWindow();
private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();

private:
    Ui::adminwindow *ui;
};

#endif // ADMINWINDOW_H
