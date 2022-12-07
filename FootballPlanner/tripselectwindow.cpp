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

    query.prepare("SELECT DISTINCT TeamName FROM TeamInformation WHERE TeamName != (:team)");
    query.bindValue(":team", "Green Bay Packers");
    query.exec();
    query.next();

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
    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    team = ui->DJTeamsComboBox->currentText();

    deleteQuery->exec("DELETE FROM FinalTrip");
    deleteQuery->exec("DELETE FROM CustomTrip");

    djAlgo performAlgo;
    performAlgo.DijkstraAlgo("Lambeau Field");

    addTeamQuery->prepare("INSERT INTO CustomTrip VALUES (:teamname)");
    addTeamQuery->bindValue(":teamname", "Green Bay Packers");
    addTeamQuery->exec();
    addTeamQuery->next();

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

    addTeamQuery->prepare("INSERT INTO CustomTrip VALUES (:teamname)");
    addTeamQuery->bindValue(":teamname", team);
    addTeamQuery->exec();
    addTeamQuery->next();

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


void tripselectwindow::on_BeginTripPushButton_clicked()
{
    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* souvModel = new QSqlQueryModel();
    QSqlQueryModel* distanceTableModel = new QSqlQueryModel();
    QSqlQuery *addQuery = new QSqlQuery(myDb);
    QSqlRecord record;
    QSqlQuery query(myDb);
    QSqlQuery queryStadName(myDb);
    QSqlQuery souvQuery(myDb);
    QSqlRecord startingSouvenir;

    QString stadiumName;

    query.exec("SELECT TeamName FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->teamComboBox->addItem(record.value(0).toString());
        queryStadName.prepare("SELECT StadiumName FROM TeamInformation WHERE TeamName = :team");
        queryStadName.bindValue(":team", record.value(0).toString());
        queryStadName.exec();
        queryStadName.next();

        stadiumName = queryStadName.value(0).toString();

        addQuery->prepare("INSERT INTO totalAmountSpentForTeams(teamName, StadiumName, amountSpent, amountIfStadiumSame) VALUES (:team, :stad, :amount, :amountSame);");
        addQuery->bindValue(":team", record.value(0).toString());
        addQuery->bindValue(":stad", stadiumName);
        addQuery->bindValue(":amount", 0.0);
        addQuery->bindValue(":amountSame", 0.0);
        addQuery->exec();
    }

    startingSouvenir = teamModel->record(0);
    souvQuery.prepare("SELECT itemName FROM souvenirList WHERE teamName = :team");
    souvQuery.bindValue(":team", startingSouvenir.value(0).toString());
    souvQuery.exec();
    souvModel->setQuery(std::move(souvQuery));

    for (int i = 0; i < souvModel->rowCount(); i++)
    {
        record = souvModel->record(i);
        ui->SouvenirComboBox->addItem(record.value(0).toString());
    }

    distanceTableModel->setQuery("SELECT * FROM FinalTrip");
    ui->customTripDistanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripDistanceTableView->setAlternatingRowColors(true);
    ui->customTripDistanceTableView->setModel(distanceTableModel);

    ui->tripStackedWidget->setCurrentIndex(5);


}


void tripselectwindow::on_pushButton_2_clicked() //frgot to rename but this is the change team souvenir button
{
    QString team;
    QSqlQuery souvQuery(myDb);
    QSqlQueryModel* souvModel = new QSqlQueryModel();
    QSqlRecord record;

    team = ui->teamComboBox->currentText();
    ui->SouvenirComboBox->clear();

    souvQuery.prepare("SELECT itemName FROM souvenirList WHERE teamName = :team");
    souvQuery.bindValue(":team", team);
    souvQuery.exec();
    souvModel->setQuery(std::move(souvQuery));

    for (int i = 0; i < souvModel->rowCount(); i++)
    {
        record = souvModel->record(i);
        ui->SouvenirComboBox->addItem(record.value(0).toString());
    }

}


void tripselectwindow::on_pushButton_3_clicked()
{

}

void tripselectwindow::on_addSouvenirButton_clicked()
{
    QString item;
    int itemQuantity;
    double itemPrice;
    double total;
    QString team;
    QString totalSaleString;
    QString stadiumName;
    string quantityString;
    bool isInt = false;
    //errorCheck

    team = ui->teamComboBox->currentText();
    item = ui->SouvenirComboBox->currentText();
    itemQuantity = ui->quantityLineEdit->text().toInt();
    quantityString = ui->quantityLineEdit->text().toStdString();

    for (char const ch : quantityString)
    {
        if (std::isdigit(ch))
        {
            isInt = true;
        }
        else
        {
            isInt = false;
        }
    }

    if (isInt == true)
    {

        QSqlQuery *prepQuery = new QSqlQuery(myDb);
        QSqlQuery *activeQuery = new QSqlQuery(myDb);
        QSqlQuery *insertQuery = new QSqlQuery(myDb);
        QSqlQuery *sameInsertQuery = new QSqlQuery(myDb);

        QSqlQuery *totalSaleQuery = new QSqlQuery(myDb);
        QSqlQueryModel* receiptQryModel = new QSqlQueryModel();
        QSqlQueryModel* totalAmountSpentQryModel = new QSqlQueryModel();


        prepQuery -> prepare("SELECT itemPrice, stadiumName FROM souvenirList WHERE itemName = :item AND teamName = :team");
        prepQuery -> bindValue(":item", item);
        prepQuery -> bindValue(":team", team);
        prepQuery -> exec();
        prepQuery -> next();

        itemPrice = prepQuery->value(0).toDouble();
        stadiumName = prepQuery->value(1).toString();
        total = itemQuantity * itemPrice;

        activeQuery->prepare("INSERT INTO teamrReceiptTable (teamName, stadiumName, itemName, itemQuantity, totalPurchasePrice) VALUES (:team, :stad, :item, :quantity, :totalSale);");
        activeQuery->bindValue(":team", team);
        activeQuery->bindValue(":stad", stadiumName);
        activeQuery->bindValue(":item", item);
        activeQuery->bindValue(":quantity", itemQuantity);
        activeQuery->bindValue(":totalSale", total);
        activeQuery->exec();
        activeQuery->next();

        insertQuery->prepare("UPDATE totalAmountSpentForTeams set amountSpent = round((SELECT  SUM(totalPurchasePrice) FROM teamrReceiptTable WHERE teamName = :team),2)  "
                             "WHERE teamName = :team");
        insertQuery->bindValue(":team", team);
        insertQuery->exec();
        insertQuery->next();


        sameInsertQuery->prepare("UPDATE totalAmountSpentForTeams set amountIfStadiumSame = round((SELECT  SUM(amountSpent) FROM totalAmountSpentForTeams WHERE StadiumName = :stad),2) WHERE StadiumName = :stad");
        sameInsertQuery->bindValue(":stad", stadiumName);
        sameInsertQuery->exec();
        sameInsertQuery->next();

        totalSaleQuery->exec("SELECT ROUND((SUM(totalPurchasePrice)), 2) AS ROUNDVALUE FROM teamrReceiptTable");
        totalSaleQuery->next();
        totalSaleString = totalSaleQuery->value(0).toString();
        totalSaleString = "Total Amount Spent: " + totalSaleString;

        ui->totalAmountSpentLabel->setText(totalSaleString);

        ui->receiptTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->receiptTableView->setAlternatingRowColors(true);

        ui->totalSpentTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->totalSpentTableView->setAlternatingRowColors(true);

        receiptQryModel->setQuery("SELECT * FROM teamrReceiptTable");
        totalAmountSpentQryModel->setQuery("SELECT * FROM totalAmountSpentForTeams");
        ui->errorCheck->setText("");

        ui->receiptTableView->setModel(receiptQryModel);
        ui->totalSpentTableView->setModel(totalAmountSpentQryModel);
    }
    else
    {
        ui->errorCheck->setText("NOT AN INT! Enter an Int Into Quanaity");
    }

}


void tripselectwindow::on_endTripPushButton_clicked()
{
    ui->tripStackedWidget->setCurrentIndex(0);
   QSqlQuery *deleteQuery = new QSqlQuery(myDb);
   QSqlQueryModel* receiptQryModel = new QSqlQueryModel();
   QSqlQueryModel* totalAmountSpentQryModel = new QSqlQueryModel();

   deleteQuery->exec("DELETE FROM teamrReceiptTable");
   deleteQuery->exec("DELETE FROM totalAmountSpentForTeams");

   deleteQuery->exec("DELETE FROM FinalTrip");
   deleteQuery->exec("DELETE FROM CustomTrip");

   ui->receiptTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->receiptTableView->setAlternatingRowColors(true);

   ui->totalSpentTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->totalSpentTableView->setAlternatingRowColors(true);

   receiptQryModel->setQuery("SELECT * FROM teamrReceiptTable");
   totalAmountSpentQryModel->setQuery("SELECT * FROM totalAmountSpentForTeams");

   ui->receiptTableView->setModel(receiptQryModel);
   ui->totalSpentTableView->setModel(totalAmountSpentQryModel);

   ui->SouvenirComboBox->clear();
   ui->teamComboBox->clear();
   ui->teamsComboBox->clear();
   ui->customTeamsComboBox->clear();

   ui->totalAmountSpentLabel->setText("");


}


void tripselectwindow::on_customTripBeginFastestPushButton_clicked()
{
    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* souvModel = new QSqlQueryModel();
    QSqlQueryModel* distanceTableModel = new QSqlQueryModel();
    QSqlQuery *addQuery = new QSqlQuery(myDb);
    QSqlRecord record;
    QSqlQuery query(myDb);
    QSqlQuery queryStadName(myDb);
    QSqlQuery souvQuery(myDb);
    QSqlRecord startingSouvenir;

    QString stadiumName;

    query.exec("SELECT TeamName FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->teamComboBox->addItem(record.value(0).toString());
        queryStadName.prepare("SELECT StadiumName FROM TeamInformation WHERE TeamName = :team");
        queryStadName.bindValue(":team", record.value(0).toString());
        queryStadName.exec();
        queryStadName.next();

        stadiumName = queryStadName.value(0).toString();

        addQuery->prepare("INSERT INTO totalAmountSpentForTeams(teamName, StadiumName, amountSpent, amountIfStadiumSame) VALUES (:team, :stad, :amount, :amountSame);");
        addQuery->bindValue(":team", record.value(0).toString());
        addQuery->bindValue(":stad", stadiumName);
        addQuery->bindValue(":amount", 0.0);
        addQuery->bindValue(":amountSame", 0.0);
        addQuery->exec();
    }

    startingSouvenir = teamModel->record(0);
    souvQuery.prepare("SELECT itemName FROM souvenirList WHERE teamName = :team");
    souvQuery.bindValue(":team", startingSouvenir.value(0).toString());
    souvQuery.exec();
    souvModel->setQuery(std::move(souvQuery));

    for (int i = 0; i < souvModel->rowCount(); i++)
    {
        record = souvModel->record(i);
        ui->SouvenirComboBox->addItem(record.value(0).toString());
    }

    distanceTableModel->setQuery("SELECT * FROM FinalTrip");
    ui->customTripDistanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripDistanceTableView->setAlternatingRowColors(true);
    ui->customTripDistanceTableView->setModel(distanceTableModel);

    ui->tripStackedWidget->setCurrentIndex(5);

}


void tripselectwindow::on_goBackPushButton_clicked()
{
    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    ui->tripStackedWidget->setCurrentIndex(0);

    deleteQuery->exec("DELETE FROM FinalTrip");

}


void tripselectwindow::on_PatriotsPushButton_clicked()
{
    QSqlQueryModel model;
    QSqlQuery query(myDb);
    QSqlQuery tripQuery(myDb);

    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* teamPlanModel = new QSqlQueryModel();
    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    deleteQuery->exec("DELETE FROM CustomTrip");
    deleteQuery->exec("DELETE FROM FinalTrip");

    ui->AllTeamTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->AllTeamTableView->setAlternatingRowColors(true);

    query.exec("SELECT DISTINCT TeamName FROM TeamInformation");
    tripQuery.exec("SELECT Team FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    teamPlanModel->setQuery(std::move(tripQuery));

    ui->AllTeamTableView->setModel(teamModel);

    ui->tripStackedWidget->setCurrentIndex(3);
}


void tripselectwindow::on_AllTeamBeginPushButton_clicked()
{
    QString team;

    QSqlQuery *addCityQuery = new QSqlQuery(myDb);
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    addCityQuery->prepare("INSERT INTO CustomTrip (TeamName) VALUES (:team)");
    addCityQuery->bindValue(":team", "New England Patriots");
    addCityQuery->exec();


    addCityQuery->prepare("INSERT INTO CustomTrip (TeamName) SELECT TeamName FROM TeamInformation WHERE TeamName != (:team)");
    addCityQuery->bindValue(":team", "New England Patriots");
    addCityQuery->exec();



    djAlgo performAlgo;
    performAlgo.CalcTripDistance();

}


void tripselectwindow::on_pushButton_clicked()
{
    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* souvModel = new QSqlQueryModel();
    QSqlQueryModel* distanceTableModel = new QSqlQueryModel();
    QSqlQuery *addQuery = new QSqlQuery(myDb);
    QSqlRecord record;
    QSqlQuery query(myDb);
    QSqlQuery queryStadName(myDb);
    QSqlQuery souvQuery(myDb);
    QSqlRecord startingSouvenir;

    QString stadiumName;

    query.exec("SELECT TeamName FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->teamComboBox->addItem(record.value(0).toString());
        queryStadName.prepare("SELECT StadiumName FROM TeamInformation WHERE TeamName = :team");
        queryStadName.bindValue(":team", record.value(0).toString());
        queryStadName.exec();
        queryStadName.next();

        stadiumName = queryStadName.value(0).toString();

        addQuery->prepare("INSERT INTO totalAmountSpentForTeams(teamName, StadiumName, amountSpent, amountIfStadiumSame) VALUES (:team, :stad, :amount, :amountSame);");
        addQuery->bindValue(":team", record.value(0).toString());
        addQuery->bindValue(":stad", stadiumName);
        addQuery->bindValue(":amount", 0.0);
        addQuery->bindValue(":amountSame", 0.0);
        addQuery->exec();
    }

    startingSouvenir = teamModel->record(0);
    souvQuery.prepare("SELECT itemName FROM souvenirList WHERE teamName = :team");
    souvQuery.bindValue(":team", startingSouvenir.value(0).toString());
    souvQuery.exec();
    souvModel->setQuery(std::move(souvQuery));

    for (int i = 0; i < souvModel->rowCount(); i++)
    {
        record = souvModel->record(i);
        ui->SouvenirComboBox->addItem(record.value(0).toString());
    }

    distanceTableModel->setQuery("SELECT * FROM FinalTrip");
    ui->customTripDistanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripDistanceTableView->setAlternatingRowColors(true);
    ui->customTripDistanceTableView->setModel(distanceTableModel);

    ui->tripStackedWidget->setCurrentIndex(5);
}


void tripselectwindow::on_DJBeginTripButton_clicked()
{
    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQueryModel* souvModel = new QSqlQueryModel();
    QSqlQueryModel* distanceTableModel = new QSqlQueryModel();
    QSqlQuery *addQuery = new QSqlQuery(myDb);
    QSqlRecord record;
    QSqlQuery query(myDb);
    QSqlQuery queryStadName(myDb);
    QSqlQuery souvQuery(myDb);
    QSqlRecord startingSouvenir;

    QString stadiumName;

    query.exec("SELECT TeamName FROM CustomTrip");

    teamModel->setQuery(std::move(query));
    for(int i=0;i<teamModel->rowCount();i++)
    {
        record = teamModel->record(i);
        ui->teamComboBox->addItem(record.value(0).toString());
        queryStadName.prepare("SELECT StadiumName FROM TeamInformation WHERE TeamName = :team");
        queryStadName.bindValue(":team", record.value(0).toString());
        queryStadName.exec();
        queryStadName.next();

        stadiumName = queryStadName.value(0).toString();

        addQuery->prepare("INSERT INTO totalAmountSpentForTeams(teamName, StadiumName, amountSpent, amountIfStadiumSame) VALUES (:team, :stad, :amount, :amountSame);");
        addQuery->bindValue(":team", record.value(0).toString());
        addQuery->bindValue(":stad", stadiumName);
        addQuery->bindValue(":amount", 0.0);
        addQuery->bindValue(":amountSame", 0.0);
        addQuery->exec();
    }

    startingSouvenir = teamModel->record(0);
    souvQuery.prepare("SELECT itemName FROM souvenirList WHERE teamName = :team");
    souvQuery.bindValue(":team", startingSouvenir.value(0).toString());
    souvQuery.exec();
    souvModel->setQuery(std::move(souvQuery));

    for (int i = 0; i < souvModel->rowCount(); i++)
    {
        record = souvModel->record(i);
        ui->SouvenirComboBox->addItem(record.value(0).toString());
    }

    distanceTableModel->setQuery("SELECT * FROM FinalTrip");
    ui->customTripDistanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customTripDistanceTableView->setAlternatingRowColors(true);
    ui->customTripDistanceTableView->setModel(distanceTableModel);

    ui->tripStackedWidget->setCurrentIndex(5);
}

