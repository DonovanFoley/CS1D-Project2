#include "menuselectwindow.h"
#include "ui_menuselectwindow.h"
#include <vector>

menuselectwindow::menuselectwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuselectwindow)
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

menuselectwindow::~menuselectwindow()
{
    delete ui;
}

void menuselectwindow::on_nflTeamsPushButton_clicked(){
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
        ui->mainMenuStackedWidget->setCurrentIndex(1);
        QSqlQuery *prepQuery = new QSqlQuery(myDb);
        QSqlQueryModel* qryModel = new QSqlQueryModel();

        ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->footBallTeamTableWidget->setAlternatingRowColors(true);

        prepQuery->prepare("SELECT TeamName FROM TeamInformation ORDER BY TeamName ASC");
        prepQuery->exec();

        qryModel -> setQuery(std::move(*prepQuery));
        ui->footBallTeamTableWidget->setModel(qryModel);
        ui->filterLabel->setText("Current Filter: NFL Team Information");
    }
    else
    {
        qDebug().noquote() << "db not found";
    }
}


void menuselectwindow::on_customTripPushButton_clicked()
{
    emit goToCustomTripPage();
}


void menuselectwindow::on_pushButton_clicked()
{
    ui->mainMenuStackedWidget->setCurrentIndex(0);
    ui->filterLabel->setText("Current Filter: ");
}


void menuselectwindow::on_stadiumNamesAndTeamsPushButton_clicked()
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

    QSqlQueryModel* qryModel = new QSqlQueryModel();

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT StadiumName, TeamName FROM TeamInformation ORDER BY StadiumName ASC");
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show Stadium Names and Teams Associated");
}


void menuselectwindow::on_nflSearchPushButton_clicked()
{
    QSqlQuery query(myDb);
    QSqlRecord record;
    QSqlQueryModel *teamsModel = new QSqlQueryModel();


    query.exec("SELECT DISTINCT TeamName FROM TeamInformation");
    teamsModel->setQuery(std::move(query));

    for(int i = 0; i < teamsModel->rowCount(); i++)
    {
        record = teamsModel->record(i);
        ui->footballTeamComboBox->addItem(record.value(0).toString());
    }
    ui->mainMenuStackedWidget->setCurrentIndex(2);
}


void menuselectwindow::on_searchPushButton_clicked()
{
    QString team;

    QSqlQueryModel* qryModel = new QSqlQueryModel();
    QSqlQuery *prepQuery = new QSqlQuery(myDb);

    team = ui->footballTeamComboBox->currentText();

    prepQuery->prepare("SELECT * FROM TeamInformation WHERE TeamName = :teamName");
    prepQuery->bindValue(":teamName", team);
    prepQuery->exec();

    ui->footballSearchTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footballSearchTableView->setAlternatingRowColors(true);

    qryModel -> setQuery(std::move(*prepQuery));
    ui->footballSearchTableView->setModel(qryModel);


}


void menuselectwindow::on_goBackSecondPushButton_clicked()
{
    ui->mainMenuStackedWidget->setCurrentIndex(0);
    ui->filterLabel->setText("Current Filter: ");
}


void menuselectwindow::on_stadiumsByDatePushButton_clicked()
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

    QSqlQueryModel* qryModel = new QSqlQueryModel();

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT StadiumName, TeamName, DateOpened FROM TeamInformation ORDER BY DateOpened ASC");
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show Stadium Names and Teams Associated by Date Opened");
}





void menuselectwindow::on_afcTeamPushButton_clicked()
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

    QSqlQueryModel* qryModel = new QSqlQueryModel();

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT TeamName, Conference FROM TeamInformation WHERE Conference = 'American Football Conference' ORDER BY TeamName");
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show AFC Teams");
}


void menuselectwindow::on_nfcTeamsPushButton_clicked()
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

    QSqlQueryModel* qryModel = new QSqlQueryModel();

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT TeamName, Conference FROM TeamInformation WHERE Conference = 'National Football Conference' ORDER BY TeamName");
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show NFC Teams");
}


void menuselectwindow::on_nfcNorthPushButton_clicked()
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

    QSqlQueryModel* qryModel = new QSqlQueryModel();
    QSqlQuery *prepQuery = new QSqlQuery(myDb);

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    prepQuery->prepare("SELECT TeamName, Division FROM TeamInformation WHERE  Division = :div ORDER BY TeamName ASC");
    prepQuery->bindValue(":div", "NFC North");
    prepQuery->exec();

    qryModel->setQuery(std::move(*prepQuery));
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show NFC North Teams");
}

void menuselectwindow::on_nflTeamSouvenir_clicked()
{
    QSqlQuery query(myDb);
    QSqlRecord record;
    QSqlQueryModel *teamsModel = new QSqlQueryModel();


    query.exec("SELECT DISTINCT TeamName FROM souvenirList");
    teamsModel->setQuery(std::move(query));

    for(int i = 0; i < teamsModel->rowCount(); i++)
    {
        record = teamsModel->record(i);
        ui->teamComboBox->addItem(record.value(0).toString());
    }
    ui->mainMenuStackedWidget->setCurrentIndex(3);
}


void menuselectwindow::on_souvenirSearchButton_clicked()
{
    ui->souvenirTableWidget->setRowCount(0);
    ui->souvenirTableWidget->setColumnCount(0);

    mapSouvenir map;
    QString team;
    QStringList teamHeaders = {"Souvenir Item" , "Price"};
    team = ui->teamComboBox->currentText();
    ui->souvenirTableWidget->insertColumn(0);
    ui->souvenirTableWidget->insertColumn(1);
    ui->souvenirTableWidget->setHorizontalHeaderLabels(teamHeaders);
    ui->souvenirTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->souvenirTableWidget->setAlternatingRowColors(true);

    mapSouvenirVector temp = map.at(team);
    for (int i = 0; i < temp.size(); i++)
    {
        QString itemName;
        double itemPrice = 0.0;

        temp.returnItemFromIndex(i, itemName,itemPrice);\
        //qDebug().noquote() << "item Price" << itemPrice;

        QTableWidgetItem* item = new QTableWidgetItem(itemName);
        QTableWidgetItem* price= new QTableWidgetItem(QString::number(itemPrice));
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        price->setFlags(price->flags() ^ Qt::ItemIsEditable);
        ui->souvenirTableWidget->insertRow(ui->souvenirTableWidget->rowCount());
        ui->souvenirTableWidget->setItem(i,0,item);
        ui->souvenirTableWidget->setItem(i,1,price);
    }

}


void menuselectwindow::on_goBackSecondPushButton_2_clicked()
{
    ui->mainMenuStackedWidget->setCurrentIndex(0);
    ui->souvenirTableWidget->setRowCount(0);
    ui->souvenirTableWidget->setColumnCount(0);
}


void menuselectwindow::on_openRoofStadiumInfo_clicked()
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

    QSqlQuery *prepQuery = new QSqlQuery(myDb);
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    QSqlQuery *countQuery = new QSqlQuery(myDb);
    QSqlQueryModel* countModel = new QSqlQueryModel();


    prepQuery->prepare("SELECT TeamName, StadiumName, RoofType FROM TeamInformation WHERE RoofType = :type");
    prepQuery->bindValue(":type", "Open");
    prepQuery->exec();

    countQuery->prepare("SELECT Distinct stadiumName, RoofType FROM TeamInformation WHERE RoofType = :type");
    countQuery->bindValue(":type", "Open");
    countQuery->exec();

    qryModel->setQuery(std::move(*prepQuery));
    countModel->setQuery(std::move(*countQuery));

    int numOfOpen = countModel->rowCount();

    ui->footBallTeamTableWidget->setModel(qryModel);
    ui->filterLabel->setText("Number of Stadiums With Open Roof Type: " + QString::number(numOfOpen));

    ui->mainMenuStackedWidget->setCurrentIndex(1);
}


void menuselectwindow::on_nflSeatingCapacity_clicked()
{
    std::vector<int> seatingCapacities;
    std::vector<QString> stadiums;
    int totalCapacity = 0;
    QString prevStadium = "";
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
    QSqlQuery *prepQuery = new QSqlQuery(myDb);
    QSqlQuery query(myDb);

    query.prepare("SELECT SeatingCapacity FROM TeamInformation ORDER BY SeatingCapacity ASC");
    query.exec();

    while (query.next())
    {
        seatingCapacities.push_back(query.value(0).toInt());
    }

    query.prepare("SELECT StadiumName FROM TeamInformation ORDER BY SeatingCapacity ASC");
    query.exec();

    while (query.next())
    {
        stadiums.push_back(query.value(0).toString());
    }

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    prepQuery->prepare("SELECT TeamName, stadiumName, SeatingCapacity FROM TeamInformation ORDER BY SeatingCapacity ASC");
    prepQuery->exec();

    qryModel->setQuery(std::move(*prepQuery));
    ui->footBallTeamTableWidget->setModel(qryModel);

    for (int i = 0; i < seatingCapacities.size(); i++) {
        totalCapacity += seatingCapacities[i];
        if (prevStadium == stadiums[i]) {
            totalCapacity -= seatingCapacities[i];
        }
        prevStadium = stadiums[i];
    }
    QString label = QString::fromStdString("Total Seating Capacity: ") + QString::number(totalCapacity);
    ui->filterLabel->setText(label);
}


void menuselectwindow::on_conferenceSort_clicked()
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

    QSqlQueryModel* qryModel = new QSqlQueryModel();
    QSqlQuery *prepQuery = new QSqlQuery(myDb);

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    prepQuery->prepare("SELECT TeamName, StadiumName, Location, Conference FROM TeamInformation ORDER BY Conference ASC");
    prepQuery->exec();

    qryModel->setQuery(std::move(*prepQuery));
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show NFL Teams Information Sorted by Conference Type");
}


void menuselectwindow::on_mainWindowButton_clicked()
{
    emit goBackToMenu();
}

