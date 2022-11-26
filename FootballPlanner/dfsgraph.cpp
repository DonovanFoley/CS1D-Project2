#include "dfsgraph.h"
#include "qdebug.h"
#include <QMessageBox>


edge::edge()
{

}

edge::edge(int userDestination, int userWeight)
{
    destinationVertexId = userDestination;
    weight = userWeight;
}

void edge::setEdgeValues(int userDestination, int userWeight)
{
    destinationVertexId = userDestination;
    weight = userWeight;
}

void edge::setWeight(int userWeight)
{
    weight = userWeight;
}

int edge::getDestinationVertexId()
{
    return destinationVertexId;
}

int edge::getWeight()
{
    return weight;
}

vertex::vertex()
{
    stateId = 0;
    stateName = "";
}

int vertex::getStateId()
{
    return stateId;
}

string vertex::getStateName()
{
    return stateName;
}

void vertex::setId(int id)
{
    stateId = id;
}

void vertex::setStateAndId(int id, string name)
{
    stateId = id;
    stateName = name;
}

void vertex::setStateName(string name)
{
    stateName = name;
}

list <edge> vertex::getEdgeList()
{
    return edgeList;
}

void vertex::addEdgetoEdgeList(int vertexId, int weight)
{
    edge e(vertexId, weight);
    edgeList.push_back(e);
}

DFSGraph::DFSGraph()
{

}
bool DFSGraph::checkIfVertexExistById(int vertexId)
{
    bool flag = false;
    for (int i = 0; i < verticies.size(); i++)
    {
        if (verticies.at(i).getStateId()== vertexId)
        {
            flag = true;
            return flag;
            break;
        }
        //return flag;
    }

    return flag;
}

bool DFSGraph::checkIfEdgeExistById(int fromVertex, int toVertex)
{
    vertex v = getVertexByID(fromVertex);
    list <edge> e;
    e = v.getEdgeList();
    bool flag = false;
    for (auto it = e.begin(); it != e.end(); it++)
    {
        if (it -> getDestinationVertexId() == toVertex)
        {
            flag = true;
            return flag;
            break;
        }
    }
    return flag;
}

void DFSGraph::addVertex(vertex newVertex)
{
    bool check = checkIfVertexExistById(newVertex.getStateId());
    if (check == true)
    {
        qDebug() << "error";
    }
    else
    {
        verticies.push_back(newVertex);
        qDebug().noquote() << "added vertex" << QString::fromStdString(newVertex.getStateName()) << newVertex.getStateId();
    }
}

vertex DFSGraph::getVertexByID(int vid)
{
    vertex temp;
    for (int i = 0; i < verticies.size(); i++)
    {
        temp = verticies.at(i);
        if (temp.getStateId() == vid)
        {
            return temp;
        }
    }
    return temp;
}

void DFSGraph::addEdgeById(int fromVertex, int toVertex, int weight)
{
    bool check1 = checkIfVertexExistById(fromVertex);
    bool check2 = checkIfVertexExistById(toVertex);

    bool check3 = checkIfEdgeExistById(fromVertex, toVertex);
    if ((check1 && check2 == true))
    {
        if (check3 == true)
        {
            qDebug().noquote() << "edge between" << QString::fromStdString(getVertexByID(fromVertex).getStateName())
                               << fromVertex << ") and "
                               << QString::fromStdString(getVertexByID(toVertex).getStateName())
                               << toVertex << ") already exist";
        }
        else
        {
            for (int i = 0; i < verticies.size(); i++)
            {
                if (verticies.at(i).getStateId() == fromVertex)
                {
                    edge e(toVertex, weight);
                    verticies.at(i).edgeList.push_back(e);
                    verticies.at(i).vertexSort();
                }
            }
            qDebug().noquote() << "edge between " << fromVertex << " and " << toVertex << " added ";
        }
    }
    else
    {
        qDebug().noquote() << "invalid id";
    }
}

void DFSGraph::DFS(vertex* startingVertex)
{
    startingVertex->isExplored = true;
    while (!startingVertex->edgeList.empty())
    {
        edge lowestEdge = startingVertex->edgeList.front();
        startingVertex->edgeList.pop_front();

        bool found = false;


        for (int i = 0; i < vertexPair.size(); i++)
        {
            pair <int,int> p = vertexPair[i];
            if (startingVertex->stateId == p.second && lowestEdge.destinationVertexId == p.first)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            qDebug().noquote() << "discovery";
            int secondVertexID = lowestEdge.destinationVertexId;
            vertex *nextDestination = &verticies[secondVertexID];

            if (!nextDestination->isExplored)
            {
                qDebug().noquote() << "discovery";

                nextDestination->previousVertex = startingVertex;;
                nextDestination->previousEdge = &lowestEdge;
                lowestEdge.edgeState = "discovery";


                discoveryEdgesOutputStart.push_back(QString::fromStdString(startingVertex->stateName));
                discoveryEdgesOutputEnd.push_back(stadiumName(lowestEdge.destinationVertexId));

                count++;
                totalDistance += lowestEdge.weight;
                totalDistanceOutput.push_back(totalDistance);
                DFS(nextDestination);
                return;
            }
            else
            {
                if (startingVertex->previousVertex != NULL &&
                    startingVertex->previousVertex->stateName == nextDestination->stateName)
                {
                    qDebug().noquote() << "entered here";
                    lowestEdge.edgeState = "discovery";
                    continue;
                }
                if (lowestEdge.edgeState == "unexplored")
                {
                    qDebug().noquote() << "back edge";
                    backEdgesOutputStart.push_back(QString::fromStdString(startingVertex->stateName));
                    backEdgesOutputEnd.push_back(stadiumName(lowestEdge.destinationVertexId));

                    lowestEdge.edgeState = "back";

                    pair <int, int> p;
                    p.first = startingVertex->stateId;
                    p.second = lowestEdge.destinationVertexId;

                    vertexPair.push_back(p);
                }
            }
        }
    }
    if (startingVertex->previousVertex != nullptr)
    {
        DFS(startingVertex->previousVertex);
    }
}

void DFSGraph::helperDFS(string name)
{
    vertex* startingVertex = NULL;
    for(int i = 0; i < verticies.size(); i++)
    {
        if (verticies[i].stateName == name)
        {
            startingVertex = &verticies[i];
        }
    }
    totalDistance = 0;
    DFS(startingVertex);
    qDebug().noquote() << "\nTotal distance traveled: " << totalDistance;
}

QString DFSGraph::stadiumName(int stadiumID)
{
    QString stadiumName;

    switch (stadiumID)
    {
        case 0: stadiumName = "Acrisure Stadium";
                break;

        case 1: stadiumName = "Allegiant Stadium";
                break;

        case 2: stadiumName = "Arrowhead Stadium";
                break;

        case 3: stadiumName = "AT&T Stadium";
                break;

        case 4: stadiumName = "Bank of America Stadium";
                break;

        case 5: stadiumName = "Caesars Superdome";
                break;

        case 6: stadiumName = "Empower Field at Mile High";
                break;

        case 7: stadiumName = "FedExField";
                break;

        case 8: stadiumName = "FirstEnergy Stadium";
                break;

        case 9: stadiumName = "Ford Field";
                break;

        case 10: stadiumName = "Gillette Stadium";
                break;

        case 11: stadiumName = "Hard Rock Stadium";
                break;

        case 12: stadiumName = "Highmark Stadium";
                break;

        case 13: stadiumName = "Lambeau Field";
                break;

        case 14: stadiumName = "Levi's Stadium";
                break;

        case 15: stadiumName = "Lincoln Financial Field";
                break;

        case 16: stadiumName = "Lucas Oil Stadium";
                break;

        case 17: stadiumName = "Lumen Field";
                break;

        case 18: stadiumName = "M&T Bank Stadium";
                break;

        case 19: stadiumName = "Mercedes-Benz Stadium";
                break;

        case 20: stadiumName = "MetLife Stadium";
                break;

        case 21: stadiumName = "Nissan Stadium";
                break;

        case 22: stadiumName = "NRG Stadium";
                break;

        case 23: stadiumName = "Paycor Stadium";
                break;

        case 24: stadiumName = "Raymond James Stadium";
                break;

        case 25: stadiumName = "SoFi Stadium";
                break;

        case 26: stadiumName = "Soldier Field";
                break;

        case 27: stadiumName = "State Farm Stadium";
                break;

        case 28: stadiumName = "TIAA Bank Field";
                break;

        case 29: stadiumName = "U.S. Bank Stadium";
                break;

        case 30: stadiumName = "Qualcomm Stadium";
                break;
    }

    return stadiumName;
}

void performDFSGraph::initGraph()
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

    vertex stadiumVertex;

    QSqlQuery query(myDb);
    QSqlQuery *addQuery = new QSqlQuery(myDb);

    query.prepare("SELECT startingStadiumId, startingStadiumName FROM nflDistances ORDER BY startingStadiumId ASC");
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
        stadiumVertex.setStateAndId(stadiumID, stadiumName.toStdString());
        qDebug().noquote() << "in while statement" << stadiumID << " added with " << stadiumName;
        graph.addVertex(stadiumVertex);
    }

    addQuery->prepare("SELECT DISTINCT startingStadiumId, endingStadiumId, distanceBetweenStadiums FROM nflDistances ORDER BY startingStadiumId ASC");
    addQuery->exec();

    while (addQuery->next())
    {
        startingStadiumId = addQuery->value(0).toInt();
        endingStatdiumId = addQuery->value(1).toInt();
        weight = addQuery->value(2).toInt();

        graph.addEdgeById(startingStadiumId,endingStatdiumId,weight);
        qDebug().noquote() << "added " << startingStadiumId << " to " << endingStatdiumId << " weight " << weight;

    }

    graph.helperDFS("U.S. Bank Stadium");

    for (int i = 0; i < graph.discoveryEdgesOutputStart.size(); i++)
    {
        discoveryStart.push_back(graph.discoveryEdgesOutputStart[i]);
        discoveryEnd.push_back(graph.discoveryEdgesOutputEnd[i]);
    }

    for (int i = 0; i < graph.backEdgesOutputStart.size(); i++)
    {
        backStart.push_back(graph.backEdgesOutputStart[i]);
        backEnd.push_back(graph.backEdgesOutputEnd[i]);
    }

    for (int i = 0; i < graph.totalDistanceOutput.size(); i++)
    {
        distanceOutput.push_back(graph.totalDistanceOutput[i]);
    }


}
