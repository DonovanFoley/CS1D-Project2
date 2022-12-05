#ifndef BFSALGO_H
#define BFSALGO_H

#include <iostream>
#include <queue>
#include <vector>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

using namespace std;

enum EdgeVal {
    invalidEdge = 0,
    unexploredEdge = 1,
    discoveryEdge = 2,
    crossEdge = 3
};

class MatrixEdge{
    public:
         EdgeVal value = EdgeVal::invalidEdge;
         MatrixEdge() {}

         MatrixEdge(EdgeVal type)
         {
             value = type;
         }
         string convertToString()
         {
             string returnValue;
              switch (value)
              {
                    case EdgeVal::invalidEdge:
                        returnValue =  "Invalid";
                        break;

                    case EdgeVal::unexploredEdge:
                        returnValue =  "Unexplored";
                        break;

                    case EdgeVal::discoveryEdge:
                        returnValue =  "Discovery";
                        break;

                    case EdgeVal::crossEdge:
                        returnValue =  "Cross";
                        break;
              }
              return returnValue;
         }
};

class matrixVertex
{
    public:
        int endingState;
        int startingState;
        int weight;
        MatrixEdge type;

        matrixVertex(int ending, int starting, int userWeight, MatrixEdge edgeType)
        {
            endingState = ending;
            startingState = starting;
            weight = userWeight;
            type = edgeType;
        }
};

class compareEdgeWeightMatrix
{
    public:
        bool operator()(matrixVertex statringWeight, matrixVertex endingWeight)
        {
            return endingWeight.weight < statringWeight.weight;
        }
};

class AdjacencyMatrix
{
    public:
        vector<int> levelOutput;
        vector<string> startingStateOutput;
        vector<string> endingStateOutput;
        vector<string> edgeTypeOutput;
        vector<int> distanceOutput;
        int totalDistance = 0;

        AdjacencyMatrix(int size)
        {
            this->size = size;
            edges = new MatrixEdge *[size];
            for (int rows = 0; rows < size; rows++)
            {
                edges[rows] = new MatrixEdge[size];
            }
            weights = new int *[size];

            for (int rows = 0; rows < size; rows++)
            {
                weights[rows] = new int[size];
                for (int columns = 0; columns < size; columns++)
                {
                    weights[rows][columns] = 0;
                }
            }

            for (int i = 0; i < size; i++)
            {
                visited.push_back(false);
            }

            QSqlDatabase myDb;

            if(QSqlDatabase::contains("qt_sql_default_connection"))
            {
                myDb = QSqlDatabase::database("qt_sql_default_connection");
            }
            else
            {
                myDb = QSqlDatabase::addDatabase("QSQLITE");
            }

            QSqlQuery query(myDb);
            QSqlQuery *addQuery = new QSqlQuery(myDb);

            query.prepare("SELECT DISTINCT startingStadiumId, startingStadiumName FROM nflDistances ORDER BY startingStadiumId ASC");
            query.exec();

            int stadiumID;
            QString stadiumName;

            int startingStadiumId;
            int endingStatdiumId;
            int weight;

            while (query.next())
            {
                stadiumName = query.value(1).toString();
                stadiumID = query.value(0).toInt();
                names.push_back(stadiumName.toStdString());
                id.push_back(stadiumID);
                qDebug().noquote() << "in while statement" << stadiumID << " added with " << stadiumName;
            }

            addQuery->prepare("SELECT DISTINCT startingStadiumId, endingStadiumId, distanceBetweenStadiums FROM nflDistances ORDER BY startingStadiumId ASC");
            addQuery->exec();

            while (addQuery->next())
            {
                startingStadiumId = addQuery->value(0).toInt();
                endingStatdiumId = addQuery->value(1).toInt();
                weight = addQuery->value(2).toInt();

                edges[startingStadiumId][endingStatdiumId].value = EdgeVal::unexploredEdge;
                weights[startingStadiumId][endingStatdiumId] = weight;
            }

        }

        void outputEdge()
        {
            for (int i = 0; i < distanceOutput.size(); i++)
            {
                qDebug().noquote() << i;
                //qDebug().noquote() << "CPRRAN" <<  distanceOutput[i];
            }
            //qDebug().noquote() <<
        }
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

        void printTotalDistance()
        {
            qDebug().noquote()<< "\nTotal distance traveled: " << totalDistance;
        }

        void addVertex(int stateId, string name)
        {
            names.push_back(name);
            id.push_back(stateId);
        }

        void addEdgeByID(int startingStateId, int endingStateId, int weight)
        {
            edges[startingStateId][endingStateId].value = EdgeVal::unexploredEdge;
            weights[startingStateId][endingStateId] = weight;
        }

        void BFSStart(string startingVertex)
        {
            int startIndex = 0;
            int level = 0;
            int endingDestination;
            int endingState;
            int startingState;
            MatrixEdge edgeType;

           // qDebug().noquote() << "in for statement" << startIndex;
            for (int i = 0; i < names.size(); i++)
            {
                //qDebug().noquote() << "in for statement" << startIndex;
                if (names[i] == startingVertex)
                {
                    startIndex = i;
                }
                //().noquote() << "in for statement" << startIndex;
            }
            //qDebug().noquote() << "in for statement" << startIndex;

            lowestEdgeVertex.push_back(startIndex);

            while (!lowestEdgeVertex.empty())
            {
                qDebug().noquote() << "\nBFS Level " << level;

                levels.clear();

                for (int i = 0; i < lowestEdgeVertex.size(); i++)
                {
                    int vert = lowestEdgeVertex[i];
                    levels.push_back(vert);
                }
                lowestEdgeVertex.clear();

                for (int i = 0; i < levels.size(); i++)
                {
                    endingDestination = levels[i];

                    for (int i = 0; i < size; i++)
                    {
                        if (edges[endingDestination][i].value == EdgeVal::unexploredEdge)
                        {

                            if (visited[i])
                            {
                                edges[endingDestination][i].value == EdgeVal::crossEdge;
                                if (edges[i][endingDestination].value != EdgeVal::invalidEdge)
                                {
                                    edges[i][endingDestination].value = EdgeVal::crossEdge;
                                }
                                vertexList.push(matrixVertex(i, endingDestination,
                                                             weights[endingDestination][i],
                                                             MatrixEdge(EdgeVal::crossEdge)));
                                continue;
                            }

                            edges[endingDestination][i].value = EdgeVal::discoveryEdge;
                            if (edges[i][endingDestination].value != EdgeVal::invalidEdge)
                            {
                                edges[i][endingDestination].value = EdgeVal::discoveryEdge;
                            }

                            visited[i] = true;
                            vertexList.push(matrixVertex(i, endingDestination,
                                                         weights[endingDestination][i],
                                                         MatrixEdge(EdgeVal::discoveryEdge)));
                        }
                    }
                    while (!vertexList.empty())
                    {
                        endingState = vertexList.top().endingState;
                        startingState = vertexList.top().startingState;
                        edgeType = vertexList.top().type;

                        if (edgeType.value == EdgeVal::discoveryEdge)
                        {
                            lowestEdgeVertex.push_back(endingState);
                            totalDistance += vertexList.top().weight;
                            //distanceOutput.push_back(totalDistance);
                        }
                        vertexList.pop();
                        startingStateOutput.push_back(names[startingState]);
                        endingStateOutput.push_back(names[endingState]);
                        edgeTypeOutput.push_back(edgeType.convertToString());
                        levelOutput.push_back(level);
                        distanceOutput.push_back(totalDistance);
                        qDebug().noquote()<<level;
                        qDebug().noquote() << QString::fromStdString(names[startingState]) << " to "
                             << QString::fromStdString(names[endingState]) << " is a "
                             << QString::fromStdString(edgeType.convertToString() ) << " Edge";
                    }
                }
                level++;
            }

        }

    private:
        vector<string> names;
        vector<int> id;
        vector<bool> visited;
        priority_queue<matrixVertex, vector<matrixVertex>, compareEdgeWeightMatrix>
                       vertexList;

        vector<int> levels;
        vector<int> lowestEdgeVertex;

        MatrixEdge **edges;
        int **weights;

        int size;

};


#endif // BFSALGO_H
