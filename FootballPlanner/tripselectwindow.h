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

private:
    Ui::tripselectwindow *ui;
};

#endif // TRIPSELECTWINDOW_H
