#include "menuselectwindow.h"
#include "ui_menuselectwindow.h"

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

    qryModel->setQuery("SELECT StadiumName, TeamName FROM TeamInformation ORDER BY DateOpened ASC");
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show Stadium Names and Teams Associated");
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

    ui->mainMenuStackedWidget->setCurrentIndex(1);

    ui->footBallTeamTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->footBallTeamTableWidget->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT TeamName, Division FROM TeamInformation WHERE  Division = 'NFC  North' ORDER BY TeamName ASC");
    ui->footBallTeamTableWidget->setModel(qryModel);

    ui->filterLabel->setText("Current Filter: Show NFC North Teams");
}

