#include "mapsouvenir.h"

item::item(QString itemName, double itemPrice)
{
      name = itemName;
      price = itemPrice;
}

item::item()
{
      name = "";
      price = 0;
}

void item::setItem(QString itemName, double itemPrice)
{
    name = itemName;
    price = itemPrice;
}

void item::returnItem(QString &itemName, double &itemPrice)
{
    itemName = name;
    itemPrice = price;
}

double item::getPrice()
{
    return price;
}


mapSouvenirVector::mapSouvenirVector(QString name)
{
    teamName = name;
}

void mapSouvenirVector::addItemToVector(QString itemName, double itemPrice)
{
    item souvenirItem(itemName, itemPrice);

    souvenirList.push_back(souvenirItem);
}

int mapSouvenirVector::size()
{
    return souvenirList.size();
}
void mapSouvenirVector::returnItemFromIndex(int index, QString &itemName, double &itemPrice)
{
    item userItem;
    userItem = souvenirList[index];
    userItem.returnItem(itemName,itemPrice);

}
void mapSouvenirVector::printList()
{
    for (int i = 0; i < souvenirList.size(); i++)
    {
        QString itemName;
        double itemPrice;

        item userItem;

        userItem = souvenirList[i];

        userItem.returnItem(itemName,itemPrice);



        cout << "Item Name: " << itemName.toStdString() << endl;
        cout << "Item Price: " << itemPrice << endl << endl;
    }
}

QString mapSouvenirVector::getName()
{
    return teamName;
}

mapSouvenir::mapSouvenir()
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

    vector<QString> teamNames;

    QSqlQuery query(myDb);
    QSqlQuery prepQuery(myDb);
    QSqlQuery *addQuery = new QSqlQuery(myDb);
    query.prepare("SELECT DISTINCT TeamName FROM TeamInformation");
    query.exec();

    QString item;
    double itemPrice;

    while (query.next())
    {
        teamNames.push_back(query.value(0).toString());
    }

    //qDebug().noquote() << "team names fetched";

    for (int i = 0; i < teamNames.size(); i++)
    {
        mapSouvenirVector temp(teamNames[i]);
        //qDebug().noquote() << temp.teamName;
        addQuery -> prepare("SELECT itemName, itemPrice FROM souvenirList WHERE teamName = (:teamName)");
        addQuery -> bindValue(":teamName", temp.teamName);
        addQuery -> exec();

        while(addQuery -> next())
        {
            item = addQuery->value(0).toString();
            itemPrice = addQuery->value(1).toDouble();
            temp.addItemToVector(item,itemPrice);
            //qDebug().noquote() << item << "itemPrice" << itemPrice;
        }

        souvenirMap.emplace(temp.teamName.toStdString(),temp);
    }
}

mapSouvenirVector mapSouvenir::at(QString name)
{
    return souvenirMap.at(name.toStdString());

}
