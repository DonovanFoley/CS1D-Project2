#ifndef DJALGO_H
#define DJALGO_H

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
            void DijkstraAlgo()
            {
                string vertex = "Lambeau Field";

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
                        qDebug().noquote() << "added ";
                        startingIndex = i;
                    }
                }

                qDebug().noquote() << startingIndex;

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
                    qDebug().noquote() << (QString::fromStdString(verticies[i].vertexName));
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
};

#endif // DJALGO_H