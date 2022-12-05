#include "tripselectwindow.h"
#include "ui_tripselectwindow.h"

tripselectwindow::tripselectwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripselectwindow)
{
    ui->setupUi(this);
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

    ui->teamsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamsTableView->setAlternatingRowColors(true);
    ui->customTripTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripTableView->setAlternatingRowColors(true);

    query.exec("SELECT DISTINCT TeamName FROM Distance");
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

    if (addTeam != 0)
    {
        QSqlQuery *addQuery = new QSqlQuery(myDb);
        QSqlQuery *startingTeamQuery = new QSqlQuery(myDb);
        QSqlQueryModel* qryModel = new QSqlQueryModel();
        QString startingTeam;

        startingTeamQuery->exec("SELECT TeamName FROM CustomTrip");
        startingTeamQuery->next();
        startingTeam = startingTeamQuery->value(0).toString();

        if (addTeam == 1)
        {
              addQuery->prepare("INSERT INTO FinalTrip VALUES ((:TeamName),(:distance))");
              addQuery->bindValue(":TeamName", startingTeam);
              addQuery->bindValue(":distance", 0);
              addQuery->exec();
              nextTeamCheck = addTeam;
        }
        else
        {

//            customTripMap map;
//            map.fullMap(startingTeam, addCity);
//            nextCityCheck = addCity;
        }
        ui->customTripTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->customTripTableView->setAlternatingRowColors(true);
        qryModel->setQuery("SELECT City, Distance_Travelled AS'Total Distance Traveled' FROM Berlin_trip");
        ui->customTripTableView->setModel(qryModel);
        //customTripNotClicked = false;
        //ui->customTripErrorLabel->setVisible(false);

    }
    else
    {
//        ui->customTripErrorLabel->setVisible(true);
//        ui->customTripErrorLabel->setText("No City Entered: Please Enter a City");
    }
}


void tripselectwindow::on_DJPushButton_clicked()
{

}

