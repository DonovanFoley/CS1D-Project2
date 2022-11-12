#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    ui->appStackedWidget->addWidget(&adminWindow); //index 2
    ui->appStackedWidget->addWidget(&mainMenu);  //index 3
    ui->appStackedWidget->addWidget(&menuSelectWindow); //index 4
    ui->appStackedWidget->addWidget(&tripSelectWindow); //index 5

    ui->appStackedWidget->setCurrentIndex(3);

    connect(&mainMenu, SIGNAL(goToMenuPage()), this, SLOT(moveMainWindowPage()));
    connect(&mainMenu, SIGNAL(goToAdminPage()), this, SLOT(moveAdminPage()));

    connect(&menuSelectWindow, SIGNAL(goToCustomTripPage()), this, SLOT(moveTripSelectWindow()));

    connect(&tripSelectWindow, SIGNAL(goToMainSelectWindow()), this, SLOT (moveMenuSelectPage()));
    connect(&adminWindow, SIGNAL(goToMainSelectWindow()), this, SLOT (moveMenuSelectPageAdmin()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveAdminPage()
{
    ui->appStackedWidget->setCurrentIndex(2);
}

void MainWindow::moveMainWindowPage()
{
    ui->appStackedWidget->setCurrentIndex(4);
}

void MainWindow::moveTripSelectWindow()
{
    ui->appStackedWidget->setCurrentIndex(5);
}

void MainWindow::moveMenuSelectPage()
{
    ui->appStackedWidget->setCurrentIndex(4);
}

void MainWindow::moveMenuSelectPageAdmin()
{
    ui->appStackedWidget->setCurrentIndex(4);
}
