#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


// button to go to login page
void MainWindow::on_pushButton_admin_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}


// button to login
void MainWindow::on_pushButton_login_clicked() {
    if(ui->lineEdit_username->text() == "admin" && ui->lineEdit_password->text() == "password") {
        ui->stackedWidget->setCurrentIndex(2);
    }

    else {
        QMessageBox::warning(this, "Login", "Username and password is not correct");
    }
}


// button to main page
void MainWindow::on_pushButton_main_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
}


// home button from admin edit page
void MainWindow::on_pushButton_homeAdminEdit_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}


// home button from main page
void MainWindow::on_pushButton_homeMainPage_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

