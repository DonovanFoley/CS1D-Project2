#ifndef DFSGRAPH_H
#define DFSGRAPH_H

#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <cctype>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

using namespace std;

class edge
{
    public:
        int destinationVertexId;
        int weight;
        string edgeState = "unexplored";

        edge();
        edge(int userDestination, int userWeight);

        void setEdgeValues(int userDestination, int userWeight);
        void setWeight(int userWeight);
        int getDestinationVertexId();
        int getWeight();


};

class vertex
{
    public:
        int stateId;
        string stateName;
        bool isExplored = false;
        list <edge> edgeList;

        vertex* previousVertex = NULL;
        edge* previousEdge = NULL;

        vertex();
        int getStateId();
        string getStateName();
        void setId(int id);
        void setStateAndId(int id, string name);
        void setStateName(string name);
        list <edge> getEdgeList();
        void addEdgetoEdgeList(int vertexId, int weight);
        void vertexSort()
        {
            edgeList.sort([](const edge &e1, const edge &e2){return e1.weight < e2.weight;});
        }
       // bool compareEdgeWeight(edge weight1, edge weight2);

};

class DFSGraph
{
    public:
        vector <vertex> verticies;
        vector <pair<int,int>> vertexPair;

        vector <QString> discoveryEdgesOutputStart;
        vector <QString> discoveryEdgesOutputEnd;
        vector <QString> backEdgesOutputStart;
        vector <QString> backEdgesOutputEnd;
        vector <int> totalDistanceOutput;

        int totalDistance = 0;
        int count = 0;

        DFSGraph();
        bool checkIfVertexExistById(int vertexId);
        bool checkIfEdgeExistById(int fromVertex, int toVertex);
        void addVertex(vertex newVertex);
        vertex getVertexByID(int vid); //vid means vertexID;
        void addEdgeById(int fromVertex, int toVertex, int weight);
        void DFS(vertex* startingVertex);
        void helperDFS(string name);
        QString stadiumName(int stadiumID);
       // void initGraph();

};

class performDFSGraph : public DFSGraph
{
    public:
        vector <QString> discoveryStart;
        vector <QString> discoveryEnd;
        vector <QString> backStart;
        vector <QString> backEnd;
        vector <int> distanceOutput;

        DFSGraph graph;
        void initGraph();
};

#endif // DFSGRAPH_H
