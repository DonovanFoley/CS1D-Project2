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

void adminwindow::on_initStartingInfoPushButton_clicked()
{
    initStartingTeams("initTeamInfo.txt");
    initStartingSouvenirs("souvenirList.txt");
    initStartingDistances("nflDistances.txt");
}

void adminwindow::on_initNewFilesPushButton_clicked()
{
    initStartingTeams("ExpansionTeams.txt");
    initStartingSouvenirs("sanDiegoSouvenirList.txt");
    initStartingDistances("newDistanceAdditionsNFL.txt");
    ifSanDiego = true;
}


void adminwindow::initStartingTeams(QString fileName)
{
    QFile file(fileName);
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }
    myDb.open();

    QTextStream inFile(&file);
    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical()<<"please make sure that you put the .txt files in debug folder!";
        qCritical()<<file.errorString();
        return;
    }

    QString teamName;
    QString stadiumName;
    QString seatingCapacity;
    QString location;
    QString roofType;
    QString surfaceType;
    int dateOpened;
    QString conference;
    QString division;
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    while(!inFile.atEnd())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO TeamInformation(TeamName, StadiumName, SeatingCapacity, Location, "
                      "RoofType, Surface, DateOpened, Conference, Division) "
                      "VALUES (:team, :stadName, :capacity, :location, :type, :surf, :open, :conf, :div)");

        teamName = inFile.readLine();
        stadiumName = inFile.readLine();
        seatingCapacity = inFile.readLine();

        location = inFile.readLine();
        roofType = inFile.readLine();
        surfaceType = inFile.readLine();

        dateOpened = inFile.readLine().toInt();
        conference = inFile.readLine();
        division = inFile.readLine();

        query.bindValue(":team", teamName);
        query.bindValue(":stadName", stadiumName);
        query.bindValue(":capacity", seatingCapacity);

        query.bindValue(":location", location);
        query.bindValue(":type", roofType);
        query.bindValue(":surf", surfaceType);

        query.bindValue(":open", dateOpened);
        query.bindValue(":conf", conference);
        query.bindValue(":div", division);

        //qDebug() << teamName << stadiumName << seatingCapacity;
        query.exec();
    }
    file.close();


    ui->teamInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamInfoTable->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT * FROM TeamInformation");
    ui->teamInfoTable->setModel(qryModel);
}

void adminwindow::initStartingDistances(QString fileName)
{
    QFile file(fileName);
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }
    myDb.open();

    QTextStream inFile(&file);
    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical()<<"please make sure that you put the .txt files in debug folder!";
        qCritical()<<file.errorString();
        return;
    }

    QString startingTeam;
    int startingStadiumID;
    QString startingStadiumName;
    int endingStadiumId;
    QString endingStadiumName;
    int distance;
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    while(!inFile.atEnd())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO nflDistances(startingTeamName, startingStadiumId, "
                      "startingStadiumName, endingStadiumId, endingStadiumName, distanceBetweenStadiums) "
                      "VALUES (:team, :stadiumId, :startingStad, :endingStadId, :endingStadName, :dist)");

        startingTeam = inFile.readLine();
        startingStadiumID = inFile.readLine().toInt();
        startingStadiumName = inFile.readLine();

        endingStadiumId = inFile.readLine().toInt();
        endingStadiumName = inFile.readLine();
        distance = inFile.readLine().toInt();

        query.bindValue(":team", startingTeam);
        query.bindValue(":stadiumId", startingStadiumID);
        query.bindValue(":startingStad", startingStadiumName);
        query.bindValue(":endingStadId", endingStadiumId);
        query.bindValue(":endingStadName", endingStadiumName);
        query.bindValue(":dist", distance);

        //qDebug() << teamName << stadiumName << seatingCapacity;
        query.exec();
    }
    file.close();


    ui->distanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->distanceTableView->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT * FROM nflDistances");
    ui->distanceTableView->setModel(qryModel);
}

void adminwindow::initStartingSouvenirs(QString fileName)
{
    QFile file(fileName);
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }
    myDb.open();

    QTextStream inFile(&file);
    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical()<<"please make sure that you put the .txt files in debug folder!";
        qCritical()<<file.errorString();
        return;
    }

    QString teamName;
    QString stadiumName;
    QString itemName;
    double itemPrice;
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    while(!inFile.atEnd())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO souvenirList(teamName, stadiumName, itemName, itemPrice) "
                      "VALUES (:team, :stad, :item, :price)");

        teamName = inFile.readLine();
        stadiumName = inFile.readLine();
        itemName = inFile.readLine();
        itemPrice = inFile.readLine().toDouble();

        query.bindValue(":team", teamName);
        query.bindValue(":stad", stadiumName);
        query.bindValue(":item", itemName);
        query.bindValue(":price", itemPrice);

        //qDebug() << teamName << stadiumName << seatingCapacity;
        query.exec();
    }
    file.close();


    ui->SouvenirTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SouvenirTableView->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT * FROM souvenirList");
    ui->SouvenirTableView->setModel(qryModel);
}
void adminwindow::on_pushButton_2_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(0);
}


void adminwindow::on_deleteTablesPushButton_clicked()
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

    QSqlQueryModel* teamQryModel = new QSqlQueryModel();
    QSqlQueryModel* distanceQryModel = new QSqlQueryModel();
    QSqlQueryModel* souvenirQryModel = new QSqlQueryModel();

    QSqlQuery *deleteQuery = new QSqlQuery(myDb);
    deleteQuery->exec("DELETE FROM nflDistances");
    deleteQuery->exec("DELETE FROM souvenirList");
    deleteQuery->exec("DELETE FROM TeamInformation");


    souvenirQryModel->setQuery("SELECT * FROM souvenirList");
    distanceQryModel->setQuery("SELECT * FROM nflDistances");
    teamQryModel->setQuery("SELECT * FROM TeamInformation");

    ui->SouvenirTableView->setModel(souvenirQryModel);
    ui->distanceTableView->setModel(distanceQryModel);
    ui->teamInfoTable->setModel(teamQryModel);
    ifSanDiego = false;

}


void adminwindow::on_pushButton_6_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(2);
}


void adminwindow::on_pushButton_9_clicked()
{
    performDFSGraph graph;
    QStringList dfsHeaders = {"Starting Stadium", "Ending Stadium", "Distance Traveled", "Edge Type"};
    ui->dfsTableWidget->insertColumn(0);
    ui->dfsTableWidget->insertColumn(1);
    ui->dfsTableWidget->insertColumn(2);
    ui->dfsTableWidget->insertColumn(3);
    ui->dfsTableWidget->setHorizontalHeaderLabels(dfsHeaders);
    ui->dfsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dfsTableWidget->setAlternatingRowColors(true);
    QString discov = "Discovery";
    QString back = "Back";

//    djAlgo performAlgo;
//    performAlgo.DijkstraAlgo();

    int counter = 0;
    graph.initGraph();
    qDebug().noquote() << graph.discoveryStart.size();

    for (int i = 0; i < graph.discoveryStart.size(); i++)
    {
        counter++;
//        QTableWidgetItem *distance = new QTableWidgetItem(QString::number(performAlgo.edgeCost[i]));
//        QTableWidgetItem *start = new QTableWidgetItem("green bay packers stadium legion]");
//        QTableWidgetItem *end = new QTableWidgetItem(QString::fromStdString(performAlgo.verticies[i].vertexName));

//        ui->dfsTableWidget->insertRow(ui->dfsTableWidget->rowCount());
//        ui->dfsTableWidget->setItem(i,0,start);
//        ui->dfsTableWidget->setItem(i,1,end);
//        ui->dfsTableWidget->setItem(i,2,distance);

        qDebug().noquote() << graph.discoveryStart.size();
        QTableWidgetItem *distance = new QTableWidgetItem(QString::number(graph.distanceOutput[i]));
        QTableWidgetItem *discoveryEdgeStart = new QTableWidgetItem(graph.discoveryStart[i]);
        QTableWidgetItem *discoveryEdgeEnd = new QTableWidgetItem(graph.discoveryEnd[i]);
        QTableWidgetItem *edgeType = new QTableWidgetItem(discov);

        distance->setFlags(distance->flags() ^ Qt::ItemIsEditable);
        discoveryEdgeStart->setFlags(discoveryEdgeStart->flags() ^ Qt::ItemIsEditable);
        discoveryEdgeEnd->setFlags(discoveryEdgeEnd->flags() ^ Qt::ItemIsEditable);
        edgeType->setFlags(edgeType->flags() ^ Qt::ItemIsEditable);

        ui->dfsTableWidget->insertRow(ui->dfsTableWidget->rowCount());
        ui->dfsTableWidget->setItem(i,0,discoveryEdgeStart);
        ui->dfsTableWidget->setItem(i,1,discoveryEdgeEnd);
        ui->dfsTableWidget->setItem(i,2,distance);
        ui->dfsTableWidget->setItem(i,3,edgeType);
    }

    for (int i = 0; i < graph.backStart.size(); i++)
    {
        QTableWidgetItem *backEdgeStart = new QTableWidgetItem(graph.backStart[i]);
        QTableWidgetItem *backEdgeEnd = new QTableWidgetItem(graph.backEnd[i]);
        QTableWidgetItem *edgeType = new QTableWidgetItem(back);

        backEdgeStart->setFlags(backEdgeStart->flags() ^ Qt::ItemIsEditable);
        backEdgeEnd->setFlags(backEdgeEnd->flags() ^ Qt::ItemIsEditable);
        edgeType->setFlags(edgeType->flags() ^ Qt::ItemIsEditable);

        ui->dfsTableWidget->insertRow(ui->dfsTableWidget->rowCount());
        ui->dfsTableWidget->setItem(ui->dfsTableWidget->rowCount()-1,0,backEdgeStart);
        ui->dfsTableWidget->setItem(ui->dfsTableWidget->rowCount()-1,1,backEdgeEnd);
        ui->dfsTableWidget->setItem(ui->dfsTableWidget->rowCount()-1,3,edgeType);
    }

    QString distanceInt = QString::number(graph.distanceOutput[counter - 1]);
    ui->adminFunctionLabel->setText("Current Function: DFS from Minnesota Vikings");
    ui->distanceLabel->setText("Total Distance Traveled: " + distanceInt);
    ui->adminStackedWidget->setCurrentIndex(3);

}


void adminwindow::on_goBackMenuAdmin2_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(1);
}


void adminwindow::on_goBackAdmin3_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(2);
    ui->dfsTableWidget->setRowCount(0);
    ui->dfsTableWidget->setColumnCount(0);
    ui->adminFunctionLabel->setText("");
    ui->distanceLabel->setText("");

}

void adminwindow::on_mstOfNFLStadiumsPushButton_clicked()
{
    QStringList dfsHeaders = {"From", "To", "Distance Traveled"};
    ui->dfsTableWidget->insertColumn(0);
    ui->dfsTableWidget->insertColumn(1);
    ui->dfsTableWidget->insertColumn(2);
    ui->dfsTableWidget->setHorizontalHeaderLabels(dfsHeaders);
    ui->dfsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dfsTableWidget->setAlternatingRowColors(true);
    int counter = 0;

    mstAlgo algo;
    algo.primMSTAlgo();

    for (int i = 0; i < algo.startingCity.size(); i++)
    {
        counter++;
        QTableWidgetItem *distance = new QTableWidgetItem(QString::number(algo.distances[i]));
        QTableWidgetItem *startingCityStart = new QTableWidgetItem(algo.startingCity[i]);
        QTableWidgetItem *endingCityStart = new QTableWidgetItem(algo.endingCity[i]);

        distance->setFlags(distance->flags() ^ Qt::ItemIsEditable);
        startingCityStart->setFlags(startingCityStart->flags() ^ Qt::ItemIsEditable);
        endingCityStart->setFlags(endingCityStart->flags() ^ Qt::ItemIsEditable);

        ui->dfsTableWidget->insertRow(ui->dfsTableWidget->rowCount());
        ui->dfsTableWidget->setItem(i,0,startingCityStart);
        ui->dfsTableWidget->setItem(i,1,endingCityStart);
        ui->dfsTableWidget->setItem(i,2,distance);
    }

    QString distanceInt = QString::number(algo.distance);
    ui->adminFunctionLabel->setText("Current Function: MST of all NFL Stadiums");
    ui->distanceLabel->setText("Total Distance Traveled: " + distanceInt);
    ui->adminStackedWidget->setCurrentIndex(3);
}


void adminwindow::on_bfsFromLaRamsPushButton_clicked()
{
    QStringList dfsHeaders = {"Level", "Starting Stadium", "Ending Stadium", "Edge Type", "Distance Traveled"};
    ui->dfsTableWidget->insertColumn(0);
    ui->dfsTableWidget->insertColumn(1);
    ui->dfsTableWidget->insertColumn(2);
    ui->dfsTableWidget->insertColumn(3);
    ui->dfsTableWidget->insertColumn(4);
    ui->dfsTableWidget->setHorizontalHeaderLabels(dfsHeaders);
    ui->dfsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dfsTableWidget->setAlternatingRowColors(true);
    int counter = 0;

    int matrixSize;
    if (ifSanDiego == false)
    {
        matrixSize = 30;
    }
    else
    {
        matrixSize = 31;
    }

    AdjacencyMatrix BFS(matrixSize);
    QString convertString = BFS.getStadiumNameFromTeamName("Los Angeles Rams");


    BFS.BFSStart(convertString.toStdString());
    BFS.printTotalDistance();

    for (int i = 0; i < BFS.startingStateOutput.size(); i++)
    {
        counter++;
        QTableWidgetItem *level = new QTableWidgetItem(QString::number(BFS.levelOutput[i]));
        QTableWidgetItem *startingCityStart = new QTableWidgetItem(QString::fromStdString(BFS.startingStateOutput[i]));
        QTableWidgetItem *endingCityStart = new QTableWidgetItem(QString::fromStdString(BFS.endingStateOutput[i]));
        QTableWidgetItem *edgeType = new QTableWidgetItem(QString::fromStdString(BFS.edgeTypeOutput[i]));
        QTableWidgetItem *distanceTrav = new QTableWidgetItem(QString::number(BFS.distanceOutput[i]));

        startingCityStart->setFlags(startingCityStart->flags() ^ Qt::ItemIsEditable);
        endingCityStart->setFlags(endingCityStart->flags() ^ Qt::ItemIsEditable);
        level->setFlags(level->flags() ^ Qt::ItemIsEditable);
        edgeType->setFlags(edgeType->flags() ^ Qt::ItemIsEditable);
        distanceTrav->setFlags(distanceTrav->flags() ^ Qt::ItemIsEditable);

        ui->dfsTableWidget->insertRow(ui->dfsTableWidget->rowCount());
        ui->dfsTableWidget->setItem(i,0,level);
        ui->dfsTableWidget->setItem(i,1,startingCityStart);
        ui->dfsTableWidget->setItem(i,2,endingCityStart);
        ui->dfsTableWidget->setItem(i,3,edgeType);
        ui->dfsTableWidget->setItem(i,4,distanceTrav);
    }

    QString distanceInt = QString::number(BFS.totalDistance);
    ui->adminFunctionLabel->setText("Current Function: BFS starting at Los Angeles Rams");
    ui->distanceLabel->setText("Total Distance Traveled: " + distanceInt);
    ui->adminStackedWidget->setCurrentIndex(3);
}


void adminwindow::on_nflTeamBermudaGrassPushButton_clicked()
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
    QSqlQuery query(myDb);

    ui->adminTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->adminTableView->horizontalHeader()->setAlternatingRowColors(true);

    query.prepare("SELECT DISTINCT TeamName, Surface FROM TeamInformation WHERE Conference = :conf AND Surface = :surf");
    query.bindValue(":conf", "National Football Conference");
    query.bindValue(":surf", "Bermuda grass");
    query.exec();

    qryModel->setQuery(std::move(query));
    ui->adminTableView->setModel(qryModel);

    int count = qryModel->rowCount();
    QString countNum = QString::number(count);

    ui->adminLabel->setText("Team Count With Bermuda Grass: " + countNum);
    ui->adminFunctionLabel_2->setText("Current Function: NFL Teams With Bermuda Grass");

    ui->adminStackedWidget->setCurrentIndex(4);

}


void adminwindow::on_goBackAdmin4_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(2);
    ui->adminFunctionLabel_2->setText("");
    ui->adminLabel->setText("");

}


void adminwindow::on_totalSeatingCapacityPushButton_clicked()
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
    QSqlQuery query(myDb);
    QSqlQuery querySum(myDb);

    ui->adminTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->adminTableView->horizontalHeader()->setAlternatingRowColors(true);

    query.prepare("SELECT DISTINCT TeamName, StadiumName, SeatingCapacity FROM TeamInformation WHERE Conference = :conf");
    query.bindValue(":conf", "National Football Conference");
    query.exec();

    querySum.prepare("SELECT DISTINCT TeamName, StadiumName, SUM(SeatingCapacity) FROM TeamInformation WHERE Conference = :conf");
    querySum.bindValue(":conf", "National Football Conference");
    querySum.exec();
    querySum.next();

    QString num = QString::number(querySum.value(2).toInt());

    qryModel->setQuery(std::move(query));
    ui->adminTableView->setModel(qryModel);

    ui->adminLabel->setText("Total Capacity:  " + num);
    ui->adminFunctionLabel_2->setText("Current Function: Total NFL Seating Capacity");

    ui->adminStackedWidget->setCurrentIndex(4);
}


void adminwindow::on_EditTableInfoPushButton_clicked()
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
    QSqlQueryModel* souvModel = new QSqlQueryModel();
    QSqlQueryModel* teamModel = new QSqlQueryModel();
    QSqlQuery query(myDb);
    QSqlRecord record;

    query.exec("SELECT DISTINCT TeamName FROM TeamInformation");
    teamModel->setQuery(std::move(query));

    for (int i = 0; i < teamModel -> rowCount(); i++)
    {
        record = teamModel->record(i);
        ui->teamBox2->addItem(record.value(0).toString());
        ui->teamBox1->addItem(record.value(0).toString());
    }

    ui->teamTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamTable->setAlternatingRowColors(true);

    ui->souvTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->souvTable->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT * FROM TeamInformation");
    ui->teamTable->setModel(qryModel);

    souvModel->setQuery("SELECT * FROM souvenirList");
    ui->souvTable->setModel(souvModel);

    ui->adminStackedWidget->setCurrentIndex(5);
}


void adminwindow::on_pushButton_8_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(1);
    ui->teamBox1->clear();
    ui->teamBox2->clear();
}

