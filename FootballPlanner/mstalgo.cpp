#include "mstalgo.h"

mstEdge::mstEdge()
{

}

mstEdge::mstEdge(int starting, int userDestination, int userWeight)
{
    startingDestinationVertexId = starting;
    destinationVertexId = userDestination;
    weight = userWeight;
}

void mstEdge::setEdgeValues(int starting, int userDestination, int userWeight)
{
    startingDestinationVertexId = starting;
    destinationVertexId = userDestination;
    weight = userWeight;
}

mstVertex::mstVertex(string name)
{
    vertexName = name;
}

void mstVertex:: addEdgesByVertexId(int starting, int ending, int weight)
{
    mstEdge newEdge;
    newEdge.setEdgeValues(starting, ending, weight);
    edges.push_back(newEdge);
}

mstAlgo::mstAlgo()
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

    for(int i = 0; i < stadiumList.size(); i++)
    {
        vertices.push_back(stadiumList[i]);
    }

    for (int i = 0; i < edgeList.size(); i++)
    {
        this->vertices[edgeList[i][0]].addEdgesByVertexId(edgeList[i][0],
                                                          edgeList[i][1],
                                                          edgeList[i][2]);

    }

    visited.resize(vertices.size()+1, false);
}

void mstAlgo::primMSTAlgo()
{
    auto comp = [](mstEdge lhs,mstEdge rhs){return lhs.weight>rhs.weight;};

    priority_queue<mstEdge,vector<mstEdge>,decltype(comp)> MSTQueue(comp);
    vector<mstVertex> mst;
    int starting = 0;
    mst.push_back(vertices[starting]);
    int total = 0;
    while(mst.size()<vertices.size())
    {
        for (int i=0;i<vertices[starting].edges.size();i++)
        {
            MSTQueue.push(vertices[starting].edges[i]);
        }
        visited[starting] = true;

        for(int i=0; i<MSTQueue.size(); i++)
        {
            if (!visited[MSTQueue.top().destinationVertexId])
            {
                mst.push_back(vertices[MSTQueue.top().destinationVertexId]);

                startingCity.push_back(QString::fromStdString(vertices[MSTQueue.top().startingDestinationVertexId].vertexName));
                endingCity.push_back(QString::fromStdString(vertices[MSTQueue.top().destinationVertexId].vertexName));
//                cout << "Going From " << vertices[MSTQueue.top().startingDestinationVertexId].vertexName
//                     << " to " << vertices[MSTQueue.top().destinationVertexId].vertexName << endl;

                starting = MSTQueue.top().destinationVertexId;
                total += MSTQueue.top().weight;
                distances.push_back(total);
                MSTQueue.pop();

                break;
            }
            else
            {
                MSTQueue.pop();
            }
        }
    }
    distance = total;
}


