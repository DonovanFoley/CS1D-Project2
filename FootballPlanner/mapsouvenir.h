/*****************************************************************//**
 * \file   mapsouvenir.h
 * \brief  This header contains the map for the souvenirs for each 
 *          team
 * 
 * \date   December 2022
 *********************************************************************/

#ifndef MAPSOUVENIR_H
#define MAPSOUVENIR_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <string>
#include <unordered_map>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>


using namespace std;

class item
{
  public:
      QString name;
      double price;

      
      item(QString itemName, double itemPrice);
      item();
      void setItem(QString itemName, double itemPrice);
      void returnItem(QString &itemName, double &itemPrice);
      double getPrice ();
};

class mapSouvenirVector
{
    public:
        QString teamName;
        vector<item> souvenirList;


        mapSouvenirVector(QString name);
        void addItemToVector(QString itemName, double itemPrice);
        void printList();
        QString getName();
        void initializeVectors();
        int size();
        void returnItemFromIndex(int index, QString &itemName, double &itemPrice);

};

class mapSouvenir
{
    public :
        unordered_map <string, mapSouvenirVector> souvenirMap;
        mapSouvenir();
        mapSouvenirVector at(QString name);

};

void initalizeVector();

#endif // MAPSOUVENIR_H
