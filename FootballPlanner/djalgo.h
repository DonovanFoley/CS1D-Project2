#ifndef DJALGO_H
#define DJALGO_H

#include "qtablewidget.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

using namespace std;
class initEdgeList
{
    public:
        vector<vector<int>> edgeList;

        void initStadiumEdgeList()
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
            int startingStadiumId;
            int endingStatdiumId;
            int weight;
            vector<int> edgeListType;
            QSqlQuery *addQuery = new QSqlQuery(myDb);

            addQuery->prepare("SELECT DISTINCT startingStadiumId, endingStadiumId, distanceBetweenStadiums FROM nflDistances ORDER BY startingStadiumId ASC");
            addQuery->exec();

            while (addQuery->next())
            {
                startingStadiumId = addQuery->value(0).toInt();
                endingStatdiumId = addQuery->value(1).toInt();
                weight = addQuery->value(2).toInt();

                edgeListType.push_back(startingStadiumId);
                edgeListType.push_back(endingStatdiumId);
                edgeListType.push_back(weight);

                edgeList.push_back(edgeListType);
                qDebug().noquote() << "added " << startingStadiumId << " to " << endingStatdiumId << " weight " << weight;
                edgeListType.pop_back();
                edgeListType.pop_back();
                edgeListType.pop_back();
            }

        }

};

class initVertexList
{
    public:
        vector<string> stadiumList;

        void initStadiumVertexList()
        {
            QSqlDatabase myDb;

            QString stadiumName;

            if(QSqlDatabase::contains("qt_sql_default_connection"))
            {
                myDb = QSqlDatabase::database("qt_sql_default_connection");
            }
            else
            {
                myDb = QSqlDatabase::addDatabase("QSQLITE");
            }
            QSqlQuery query(myDb);

            query.prepare("SELECT DISTINCT startingStadiumId, startingStadiumName FROM nflDistances ORDER BY startingStadiumId ASC");
            query.exec();

            while (query.next())
            {
                stadiumName = query.value(1).toString();
                stadiumName.toStdString();
                qDebug().noquote() << "in while statement" << stadiumName << " added with " << stadiumName;
                stadiumList.push_back(stadiumName.toStdString());
            }
        }
};

class DjVertex
{
    public:
        string vertexName;
        vector<int> vertexEdges;
        vector<int> vertexWeights;

        DjVertex(string name)
        {
            vertexName = name;
        }

        void addEdgeByVertex(int index, int weight)
        {
            vertexEdges.push_back(index);
            vertexWeights.push_back(weight);
        }


    private:
};

class djAlgo :public initEdgeList, initVertexList
{
    public:
    vector<vector<int>> edgeList;
    vector<string> stadiumList;
    vector<DjVertex> verticies;
            vector<int> edgeCost;
            vector<int> edgeParents;
            vector<int> cloudQueue;
            vector<int> newCloudQueue;
            vector <QString> outputString;
            vector<int> costString;

            djAlgo()
            {
                QSqlDatabase myDb;

                QString stadiumName;

                if(QSqlDatabase::contains("qt_sql_default_connection"))
                {
                    myDb = QSqlDatabase::database("qt_sql_default_connection");
                }
                else
                {
                    myDb = QSqlDatabase::addDatabase("QSQLITE");
                }
                QSqlQuery query(myDb);

                int startingStadiumId;
                int endingStatdiumId;
                int weight;
                vector<int> edgeListType;
                QSqlQuery *addQuery = new QSqlQuery(myDb);

                addQuery->prepare("SELECT DISTINCT startingStadiumId, endingStadiumId, distanceBetweenStadiums FROM nflDistances ORDER BY startingStadiumId ASC");
                addQuery->exec();

                while (addQuery->next())
                {
                    startingStadiumId = addQuery->value(0).toInt();
                    endingStatdiumId = addQuery->value(1).toInt();
                    weight = addQuery->value(2).toInt();

                    edgeListType.push_back(startingStadiumId);
                    edgeListType.push_back(endingStatdiumId);
                    edgeListType.push_back(weight);

                    edgeList.push_back(edgeListType);
                    qDebug().noquote() << "added " << startingStadiumId << " to " << endingStatdiumId << " weight " << weight;
                    edgeListType.pop_back();
                    edgeListType.pop_back();
                    edgeListType.pop_back();
                }

                query.prepare("SELECT DISTINCT startingStadiumId, startingStadiumName FROM nflDistances ORDER BY startingStadiumId ASC");
                query.exec();

                while (query.next())
                {
                    stadiumName = query.value(1).toString();
                    stadiumName.toStdString();
                    qDebug().noquote() << "in while statement" << stadiumName << " added with " << stadiumName;
                    stadiumList.push_back(stadiumName.toStdString());
                }

                for (int i = 0; i < stadiumList.size(); i++)
                {
                    verticies.push_back(stadiumList[i]);
                }

                for (int i = 0; i < edgeList.size(); i++)
                {
                    verticies[edgeList[i][0]].addEdgeByVertex(edgeList[i][1], edgeList[i][2]);
                }
            }

            bool isFound(int index)
            {
                return -2 != edgeParents[index];
            }

            void cost(int index)
            {
                vector<int> adjacentEdge;
                vector<int> weightCost;
                int lowestEdgeDistance;
                int lowestEdgeIndex;
                int cost;
                int parentIndex;

                for(int i = 0; i < verticies[index].vertexEdges.size(); i++)
                {
                    if (isFound(verticies[index].vertexEdges[i]))
                    {
                        adjacentEdge.push_back(verticies[index].vertexEdges[i]);
                        weightCost.push_back(weightReturn(index, verticies[index].vertexEdges[i]));
                    }
                }

                lowestEdgeDistance = 99999;
                lowestEdgeIndex = -1;

                for (int i = 0; i < weightCost.size(); i++)
                {
                    cost = weightCost[i] + edgeCost[adjacentEdge[i]];

                    if(cost < lowestEdgeDistance)
                    {
                        lowestEdgeDistance = cost;
                        lowestEdgeIndex    = i;
                    }
                }

                parentIndex = adjacentEdge[lowestEdgeIndex];
                edgeCost[index] = lowestEdgeDistance;
                edgeParents[index] = parentIndex;
            }

            void addAdjacentEdges(int index)
            {
                for (int i = 0; i < verticies[index].vertexEdges.size(); i++)
                {
                    if(!isFound(verticies[index].vertexEdges[i]))
                    {
                        newCloudQueue.push_back(verticies[index].vertexEdges[i]);
                    }
                }
            }
            void DijkstraAlgo(string vertex)
            {

                edgeCost.clear();
                edgeParents.clear();
                cloudQueue.clear();
                newCloudQueue.clear();

                edgeParents.resize(verticies.size(), -2);
                edgeCost.resize(verticies.size(), 999999);

                int startingIndex;

                for (int i = 0; i < verticies.size(); i++)
                {
                    if (verticies[i].vertexName == vertex)
                    {
                        //qDebug().noquote() << "added ";
                        startingIndex = i;
                    }
                }

                //qDebug().noquote() << startingIndex;

                edgeCost[startingIndex] = 0;
                edgeParents[startingIndex] = -1;

                cloudQueue.push_back(startingIndex);
                while (!cloudQueue.empty())
                {
                    for (int i = 0; i < cloudQueue.size(); i++)
                    {
                        if (cloudQueue[i] != startingIndex && isFound(cloudQueue[i]))
                        {
                            continue;
                        }

                        if(cloudQueue[i] != startingIndex)
                        {
                            cost(cloudQueue[i]);
                        }

                        addAdjacentEdges(cloudQueue[i]);
                    }

                    cloudQueue.clear();

                    for (int i = 0; i < newCloudQueue.size(); i++)
                    {
                        cloudQueue.push_back(newCloudQueue[i]);
                    }
                    newCloudQueue.clear();
                }

                shortestPath(vertex);
                //print();

            }

            int weightReturn(int startingIndex, int destinationIndex)
            {
                for (int i = 0; i < verticies[startingIndex].vertexEdges.size(); i++)
                {
                    if (destinationIndex == verticies[startingIndex].vertexEdges[i])
                    {
                        return verticies[startingIndex].vertexWeights[i];
                    }
                }
            }


            void shortestPath(string start)
            {
                for (int i = 0; i < edgeCost.size(); i++)
                {
                    //().noquote() << (QString::fromStdString(verticies[i].vertexName));
                    outputString.push_back(QString::fromStdString(verticies[i].vertexName));
                    costString.push_back(edgeCost[i]);
                }
            }

//            void print()
//            {
//                cout << endl;

//                for (int i = 0; i < edgeCost.size(); i++)
//                {
//                    cout << "Cost from Parent " << stadiumName(edgeParents[i]) << " ID: " << edgeParents[i]
//                         << " to " << verticies[i].vertexName << " = " << edgeCost[i] << endl;
//                }
//                cout << endl;
//            }


            QString getStadiumNameFromTeamName(QString teamName)
            {
               QString stadiumName;

               QSqlDatabase myDb;

               if(QSqlDatabase::contains("qt_sql_default_connection"))
               {
                   myDb = QSqlDatabase::database("qt_sql_default_connection");
               }
               else
               {
                   myDb = QSqlDatabase::addDatabase("QSQLITE");
               }

               QSqlQuery *searchQuery = new QSqlQuery(myDb);
               searchQuery->prepare("SELECT StadiumName FROM TeamInformation where TeamName = :name");
               searchQuery->bindValue(":name", teamName);
               searchQuery->exec();
               searchQuery->next();

               stadiumName = searchQuery->value(0).toString();
               return stadiumName;
            }

            int getStadiumIdFromStadiumName(QString stadiumName)
            {
                int stadiumID;

                QSqlDatabase myDb;

                if(QSqlDatabase::contains("qt_sql_default_connection"))
                {
                    myDb = QSqlDatabase::database("qt_sql_default_connection");
                }
                else
                {
                    myDb = QSqlDatabase::addDatabase("QSQLITE");
                }

                QSqlQuery *searchQuery = new QSqlQuery(myDb);
                searchQuery->prepare("SELECT DISTINCT startingStadiumId FROM nflDistances where startingStadiumName = :name");
                searchQuery->bindValue(":name", stadiumName);
                searchQuery->exec();
                searchQuery->next();

                stadiumID = searchQuery->value(0).toInt();
                return stadiumID;

            }

            QString stadiumName(int stadiumID)
            {
                QString stadiumName;

                 QSqlDatabase myDb;

                if(QSqlDatabase::contains("qt_sql_default_connection"))
                {
                    myDb = QSqlDatabase::database("qt_sql_default_connection");
                }
                else
                {
                    myDb = QSqlDatabase::addDatabase("QSQLITE");
                }

                QSqlQuery *searchQuery = new QSqlQuery(myDb);
                searchQuery->prepare("SELECT DISTINCT startingStadiumName FROM nflDistances WHERE startingStadiumId = :id");
                searchQuery->bindValue(":id", stadiumID);
                searchQuery->exec();
                searchQuery->next();

                stadiumName = searchQuery->value(0).toString();
                return stadiumName;
            }

            void CustomOrderTrip()
            {
                QString stadium;
                QString prevStadium;
                int distance = 0;
                QSqlDatabase myDb;

                if(QSqlDatabase::contains("qt_sql_default_connection"))
                {
                    myDb = QSqlDatabase::database("qt_sql_default_connection");
                }
                else
                {
                    myDb = QSqlDatabase::addDatabase("QSQLITE");
                }

                if (myDb.open())
                {
                    qDebug().noquote() << "db found and open";
                }
                else
                {
                    qDebug().noquote() << "db not found";
                }

                QSqlQueryModel model;//model is readonly access to query results
                QSqlQuery query(myDb);
                QSqlQuery *addQuery = new QSqlQuery(myDb);
                query.prepare("SELECT TeamName FROM CustomTrip");
                query.exec();
                std::vector<QString> team_names;

                while (query.next())
                {
                    team_names.push_back(query.value(0).toString());
                }

                for (int i = 0; i < team_names.size(); i++) {
                    if (i == 0) {
                        addQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
                        addQuery->bindValue(":teamname", team_names[i]);
                        qDebug().noquote() << "COOLNANN" << team_names[i];
                        addQuery->bindValue(":distance", 0);
                        addQuery->exec();
                        addQuery->next();
                    }
                    else {
                        qDebug().noquote() << "COOLNANN" << team_names[i];
                        stadium = getStadiumNameFromTeamName(team_names[i]);
                        DijkstraAlgo(stadium.toStdString());
                        prevStadium = getStadiumNameFromTeamName(team_names[i - 1]);
                        if (prevStadium == stadium) {
                            addQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
                            addQuery->bindValue(":teamname", team_names[i]);
                            addQuery->bindValue(":distance", distance);
                            addQuery->exec();
                            addQuery->next();
                        }
                        else {
                        for (int j = 0; j < edgeCost.size(); j++) {
                            if (prevStadium == QString::fromStdString(verticies[j].vertexName)) {
                                distance += edgeCost[j];
                            }
                        }
                        addQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
                        addQuery->bindValue(":teamname", team_names[i]);
                        addQuery->bindValue(":distance", distance);
                        addQuery->exec();
                        addQuery->next();
                        }
                    }
                }
            }

            void CalcTripDistance()
            {
                QString stadium;
                QString compareStadium;
                QString closestTeamName;
                int distance = 0;
                int temp = 0;
                std::vector<QString> team_names;
                QSqlDatabase myDb;

                if(QSqlDatabase::contains("qt_sql_default_connection"))
                {
                    myDb = QSqlDatabase::database("qt_sql_default_connection");
                }
                else
                {
                    myDb = QSqlDatabase::addDatabase("QSQLITE");
                }

                if (myDb.open())
                {
                    qDebug().noquote() << "db found and open";
                }
                else
                {
                    qDebug().noquote() << "db not found";
                }

                QSqlQueryModel model;//model is readonly access to query results
                QSqlQuery query(myDb);
                QSqlQuery *addQuery = new QSqlQuery(myDb);
                query.prepare("SELECT TeamName FROM CustomTrip");
                query.exec();

                while (query.next())
                {
                    team_names.push_back(query.value(0).toString());
                    qDebug().noquote() << " PLSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS " << query.value(0).toString();
                }


                int teamNum = team_names.size();


                addQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
                addQuery->bindValue(":teamname", team_names[0]);
                addQuery->bindValue(":distance", 0);
                addQuery->exec();
                addQuery->next();
                closestTeamName = team_names[0];
                qDebug().noquote() << "closet teamname starting: " << closestTeamName;

                stadium = getStadiumNameFromTeamName(closestTeamName);
                qDebug().noquote() << "stadium starting: " << stadium;
                DijkstraAlgo(stadium.toStdString());

                for (int n = 0; n < team_names.size(); n++) {
                    if (closestTeamName == team_names[n]) {
                        team_names.erase(team_names.begin() + n);
                    }
                }

                while (teamNum - 1 > 0) {
                    temp = 100000;
                    for (int j = 0; j < team_names.size(); j++) {
                        qDebug().noquote() << "team_names[j] giong into compare stadium: " << team_names[j];

                        compareStadium = getStadiumNameFromTeamName(team_names[j]);
                        qDebug().noquote() << "comp stadium: " << compareStadium;
                         qDebug().noquote() << "closet teamname stadium: " << closestTeamName;

//                        if (compareStadium == getStadiumNameFromTeamName(closestTeamName)) {
//                            temp = 0;
//                            qDebug().noquote() << "team_names[j] for closest teamname" << team_names[j];
//                            closestTeamName = team_names[j];
//                        }
                        //else {
                            for (int k = 0; k < edgeCost.size(); k++)
                            {
                                qDebug().noquote() << " EDGE " << QString::fromStdString(verticies[k].vertexName);
                                qDebug().noquote() << "compare stadium" << compareStadium;
                                if (compareStadium == QString::fromStdString(verticies[k].vertexName))
                                {
                                    if (edgeCost[k] < temp)
                                    {
                                        temp = edgeCost[k];
                                        closestTeamName = team_names[j];
                                        qDebug().noquote() << "closet teamname forloop k: " << closestTeamName;
                                    }
                                }
                            }
                        //}
                    }
                    distance += temp;
                    addQuery->prepare("INSERT INTO FinalTrip VALUES (:teamname, :distance)");
                    addQuery->bindValue(":teamname", closestTeamName);
                    addQuery->bindValue(":distance", distance);
                    addQuery->exec();
                    addQuery->next();

                    qDebug().noquote() << "closet team name" << closestTeamName;
                    stadium = getStadiumNameFromTeamName(closestTeamName);
                    qDebug().noquote() << "stadium" << stadium;
                    DijkstraAlgo(stadium.toStdString());
                    for (int n = 0; n < team_names.size(); n++) {
                        if (closestTeamName == team_names[n]) {
                            team_names.erase(team_names.begin() + n);
                        }
                    }
                    teamNum--;
                }
            }
};

#endif // DJALGO_H
