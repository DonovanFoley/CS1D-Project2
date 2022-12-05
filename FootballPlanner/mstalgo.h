#ifndef MSTALGO_H
#define MSTALGO_H

#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

using namespace std;

class mstEdge
{
    public:
        int startingDestinationVertexId;
        int destinationVertexId;
        int weight;

        mstEdge();
        mstEdge(int starting, int userDestination, int userWeight);
        void setEdgeValues(int starting, int userDestination, int userWeight);

};

class mstVertex
{
    public:
        string vertexName;
        vector<mstEdge> edges;

        mstVertex(string name);
        void addEdgesByVertexId(int starting, int ending, int weight);

};

class mstAlgo
{
    public:
        vector<vector<int>> edgeList;
        vector<string> stadiumList;

        vector<vector<int>> edgesListed;
        vector<mstVertex> vertices;
        vector<bool> visited;

        vector<QString> startingCity;
        vector<QString> endingCity;
        vector<int>distances;
        int distance;

        mstAlgo();
        void primMSTAlgo();

};

#endif // MSTALGO_H
