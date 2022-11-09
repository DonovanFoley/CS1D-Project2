#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

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


void MainWindow::on_stadiumNamePushButton_clicked() {
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    QSqlQueryModel* qryModel = new QSqlQueryModel();

    ui->footballTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footballTableView->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT StadiumName, TeamName FROM TeamInformation ORDER BY StadiumName ASC");
    ui->footballTableView->setModel(qryModel);


}


void MainWindow::on_nflTeamsPushButton_clicked(){
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    if(myDb.open())
    {
        QSqlQuery *prepQuery = new QSqlQuery(myDb);
        QSqlQueryModel* qryModel = new QSqlQueryModel();

        ui->footballTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->footballTableView->setAlternatingRowColors(true);

        prepQuery->prepare("SELECT TeamName, Conference FROM TeamInformation WHERE Conference = :conference ORDER BY TeamName ASC");
        prepQuery->bindValue(":conference", "National Football Conference");
        prepQuery->exec();

        qryModel -> setQuery(std::move(*prepQuery));
        ui->footballTableView->setModel(qryModel);
    }
    else
    {
        qDebug().noquote() << "db not found";
    }

}


void MainWindow::on_searchTeamPushBUtton_clicked(){
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    if(myDb.open())
    {
        QString searchTeam;

        searchTeam = ui->searchFootballTeamLineEdit->text();

        qDebug().noquote() << "values" << searchTeam;

        QSqlQuery *prepQuery = new QSqlQuery(myDb);
        QSqlQueryModel* qryModel = new QSqlQueryModel();

        prepQuery->prepare("SELECT * FROM TeamInformation WHERE TeamName = :teamName");
        prepQuery->bindValue(":teamName", searchTeam);
        prepQuery->exec();

        qryModel -> setQuery(std::move(*prepQuery));
        ui->footballTableView->setModel(qryModel);

        ui->footballTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->footballTableView->setAlternatingRowColors(true);
    }
    else
    {
        qDebug().noquote() << "db not found";
    }
}

