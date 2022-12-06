#include "tripselectwindow.h"
#include "ui_tripselectwindow.h"
#include "djalgo.h"
#include <QLabel>
#include <QObject>

tripselectwindow::tripselectwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripselectwindow)
{
    ui->setupUi(this);
    ui->tripStackedWidget->setCurrentIndex(0);
}

tripselectwindow::~tripselectwindow()
{
    delete ui;
}

void tripselectwindow::on_mainMenuPushButton_clicked()
{
    emit goToMainSelectWindow();
}


void tripselectwindow::on_OrderPushButton_clicked()
{

    QSqlQueryModel model;
    QSqlQuery query(myDb);
    QSqlQuery tripQuery(myDb);

    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* teamPlanModel = new QSqlQueryModel();
    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    deleteQuery->exec("DELETE FROM CustomTrip");
    deleteQuery->exec("DELETE FROM FinalTrip");

    ui->teamsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamsTableView->setAlternatingRowColors(true);
    ui->customTripTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripTableView->setAlternatingRowColors(true);

    query.exec("SELECT DISTINCT TeamName FROM TeamInformation");
    tripQuery.exec("SELECT Team FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    teamPlanModel->setQuery(std::move(tripQuery));

    ui->teamsTableView->setModel(teamModel);
    ui->customTripTableView->setModel(teamPlanModel);


    QSqlRecord record;
    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->teamsComboBox->addItem(record.value(0).toString());
    }


    ui->tripStackedWidget->setCurrentIndex(4);
    count = 1; //setting next city check to 1;
    addTeam = 0;//resetting the addcity count;


}


void tripselectwindow::on_addOrderTeamPushButton_clicked()
{
    QString team;

    QSqlQuery *addCityQuery = new QSqlQuery(myDb);
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    if (ui->teamsComboBox->count() != 0)
    {
        team = ui->teamsComboBox->currentText();

        addCityQuery->prepare("INSERT INTO CustomTrip (TeamName) VALUES (:team)");
        addCityQuery->bindValue(":team", team);
        addCityQuery->exec();

        qryModel->setQuery("SELECT TeamName FROM CustomTrip");

        ui->customTripTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->customTripTableView->setAlternatingRowColors(true);
        ui->customTripTableView->setModel(qryModel);

        ui->teamsComboBox->removeItem(ui->teamsComboBox->currentIndex());
        addTeam++;
        //ui->customTripErrorLabel->setVisible(false);
    }
    else
    {
        //ui->customTripErrorLabel->setVisible(true);
        //ui->customTripErrorLabel->setText("No More Cities to Add: Press Finalize Trip and Begin");
    }
}


void tripselectwindow::on_calcDistancePushButton_clicked()
{
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

        djAlgo performAlgo;
        performAlgo.CustomOrderTrip();

}


void tripselectwindow::on_DJPushButton_clicked()
{
    QSqlQueryModel model;
    QSqlQuery query(myDb);
    QSqlQuery tripQuery(myDb);

    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* teamPlanModel = new QSqlQueryModel();
    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    deleteQuery->exec("DELETE FROM CustomTrip");
    deleteQuery->exec("DELETE FROM FinalTrip");

    query.exec("SELECT DISTINCT TeamName FROM TeamInformation");

    teamModel->setQuery(std::move(query));

    QSqlRecord record;

    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->DJTeamsComboBox->addItem(record.value(0).toString());
    }

    ui->tripStackedWidget->setCurrentIndex(1);
}


void tripselectwindow::on_DJSelectPushButton_clicked()
{
    QString team;
    QString stadium;
    int distance;
    QSqlQuery *addTeamQuery = new QSqlQuery(myDb);

    team = ui->DJTeamsComboBox->currentText();

    djAlgo performAlgo;
    performAlgo.DijkstraAlgo("Lambeau Field");

    addTeamQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
    addTeamQuery->bindValue(":teamname", "Green Bay Packers");
    addTeamQuery->bindValue(":distance", 0);
    addTeamQuery->exec();
    addTeamQuery->next();

    addTeamQuery->prepare("SELECT StadiumName From TeamInformation WHERE TeamName = :team");
    addTeamQuery->bindValue(":team", team);
    addTeamQuery->exec();
    addTeamQuery->next();
    stadium = addTeamQuery->value(0).toString();

    for (int i = 0; i < performAlgo.edgeCost.size(); i++) {
        if (stadium == QString::fromStdString(performAlgo.verticies[i].vertexName)) {
            distance = performAlgo.edgeCost[i];
        }
    }

    addTeamQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
    addTeamQuery->bindValue(":teamname", team);
    addTeamQuery->bindValue(":distance", distance);
    addTeamQuery->exec();
    addTeamQuery->next();

}


void tripselectwindow::on_CustomPushButton_clicked()
{
    QSqlQueryModel model;
    QSqlQuery query(myDb);
    QSqlQuery tripQuery(myDb);

    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* teamPlanModel = new QSqlQueryModel();
    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    deleteQuery->exec("DELETE FROM CustomTrip");
    deleteQuery->exec("DELETE FROM FinalTrip");

    ui->teamsCustomTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamsCustomTableView->setAlternatingRowColors(true);
    ui->customTripTableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripTableView_2->setAlternatingRowColors(true);

    query.exec("SELECT DISTINCT TeamName FROM TeamInformation");
    tripQuery.exec("SELECT Team FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    teamPlanModel->setQuery(std::move(tripQuery));

    ui->teamsCustomTableView->setModel(teamModel);
    ui->customTripTableView_2->setModel(teamPlanModel);


    QSqlRecord record;
    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->customTeamsComboBox->addItem(record.value(0).toString());
    }


    ui->tripStackedWidget->setCurrentIndex(2);
    count = 1; //setting next city check to 1;
    addTeam = 0;//resetting the addcity count;

}


void tripselectwindow::on_addCustomTeamPushButton_clicked()
{
    QString team;

    QSqlQuery *addCityQuery = new QSqlQuery(myDb);
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    if (ui->customTeamsComboBox->count() != 0)
    {
        team = ui->customTeamsComboBox->currentText();

        addCityQuery->prepare("INSERT INTO CustomTrip (TeamName) VALUES (:team)");
        addCityQuery->bindValue(":team", team);
        addCityQuery->exec();

        qryModel->setQuery("SELECT TeamName FROM CustomTrip");

        ui->customTripTableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->customTripTableView_2->setAlternatingRowColors(true);
        ui->customTripTableView_2->setModel(qryModel);

        ui->customTeamsComboBox->removeItem(ui->customTeamsComboBox->currentIndex());
        addTeam++;
        //ui->customTripErrorLabel->setVisible(false);
    }
    else
    {
        //ui->customTripErrorLabel->setVisible(true);
        //ui->customTripErrorLabel->setText("No More Cities to Add: Press Finalize Trip and Begin");
    }
}


void tripselectwindow::on_calcCustomDistancePushButton_clicked()
{
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

        djAlgo performAlgo;
        performAlgo.CalcTripDistance();
}

