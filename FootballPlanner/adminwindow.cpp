#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>

adminwindow::adminwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwindow)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("./Project2DB.db");
    if (db.open())
    {
        qDebug().noquote() << "db found and open";
    }
    else
    {
        qDebug().noquote() << "db not found";
    }

    ui->setupUi(this);
}

adminwindow::~adminwindow()
{
    delete ui;
}

void adminwindow::on_pushButton_login_clicked(){
    if(ui->lineEdit_username->text() == "admin" && ui->lineEdit_password->text() == "password") {
        ui->adminStackedWidget->setCurrentIndex(1);
    }

    else {
        QMessageBox::warning(this, "Login", "Username and password is not correct");
    }

}


void adminwindow::on_pushButton_clicked()
{
    emit goToMainSelectWindow();
}

