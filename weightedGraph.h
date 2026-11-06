#ifndef H_weightedGraph
#define H_weightedGraph

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <string>
#include "graphType.h"

using namespace std;

class weightedGraphType : public graphType
{
public:
    void createWeightedGraph();
    void createWeightedGraph(const string& fileName);
    void shortestPath(int vertex);
    void printShortestDistance(int vertex);
    int getSize() const;

    weightedGraphType(int size = 0);
    ~weightedGraphType();

protected:
    double** weights;
    double* smallestWeight;
};

void weightedGraphType::createWeightedGraph()
{
    string fileName;

    cout << "Enter input file name: ";
    cin >> fileName;

    createWeightedGraph(fileName);
}

void weightedGraphType::createWeightedGraph(const string& fileName)
{
    ifstream infile(fileName);

    if (!infile)
    {
        cout << "Cannot open input file." << endl;
        return;
    }

    if (gSize != 0)
        clearGraph();

    int newSize;
    infile >> newSize;

    if (!infile || newSize < 0 || newSize > maxSize)
    {
        cout << "Invalid graph size in input file." << endl;
        gSize = 0;
        infile.close();
        return;
    }

    gSize = newSize;

    for (int i = 0; i < gSize; i++)
    {
        for (int j = 0; j < gSize; j++)
            weights[i][j] = (i == j) ? 0.0 : DBL_MAX;
    }

    int vertex;
    int adjacentVertex;

    for (int i = 0; i < gSize; i++)
    {
        if (!(infile >> vertex) || vertex < 0 || vertex >= gSize)
        {
            cout << "Invalid vertex data in input file." << endl;
            clearGraph();
            infile.close();
            return;
        }

        infile >> adjacentVertex;

        while (infile && adjacentVertex != -999)
        {
            if (adjacentVertex < 0 || adjacentVertex >= gSize)
            {
                cout << "Invalid adjacent vertex in input file." << endl;
                clearGraph();
                infile.close();
                return;
            }

            graph[vertex].insertLast(adjacentVertex);
            infile >> adjacentVertex;
        }
    }

    for (int i = 0; i < gSize; i++)
    {
        if (!(infile >> vertex) || vertex < 0 || vertex >= gSize)
        {
            cout << "Invalid weight data in input file." << endl;
            clearGraph();
            infile.close();
            return;
        }

        infile >> adjacentVertex;

        while (infile && adjacentVertex != -999)
        {
            double edgeWeight;

            if (!(infile >> edgeWeight) || edgeWeight < 0)
            {
                cout << "Invalid edge weight in input file." << endl;
                clearGraph();
                infile.close();
                return;
            }

            if (adjacentVertex < 0 || adjacentVertex >= gSize)
            {
                cout << "Warning: ignoring edge to invalid vertex "
                    << adjacentVertex << " in row " << vertex << "." << endl;
            }
            else
            {
                weights[vertex][adjacentVertex] = edgeWeight;
            }

            infile >> adjacentVertex;
        }
    }

    infile.close();
}

void weightedGraphType::shortestPath(int vertex)
{
    if (vertex < 0 || vertex >= gSize)
        return;

    for (int j = 0; j < gSize; j++)
        smallestWeight[j] = weights[vertex][j];

    bool* weightFound = new bool[gSize];

    for (int j = 0; j < gSize; j++)
        weightFound[j] = false;

    weightFound[vertex] = true;
    smallestWeight[vertex] = 0;

    for (int i = 0; i < gSize - 1; i++)
    {
        double minWeight = DBL_MAX;
        int v = -1;

        for (int j = 0; j < gSize; j++)
        {
            if (!weightFound[j] && smallestWeight[j] < minWeight)
            {
                v = j;
                minWeight = smallestWeight[j];
            }
        }

        if (v == -1)
            break;

        weightFound[v] = true;

        for (int j = 0; j < gSize; j++)
        {
            if (!weightFound[j] && weights[v][j] != DBL_MAX &&
                minWeight + weights[v][j] < smallestWeight[j])
            {
                smallestWeight[j] = minWeight + weights[v][j];
            }
        }
    }

    delete[] weightFound;
}

void weightedGraphType::printShortestDistance(int vertex)
{
    cout << "Source Vertex: " << vertex << endl;
    cout << "Shortest Distance from Source to each Vertex." << endl;
    cout << "Vertex  Shortest_Distance" << endl;

    for (int j = 0; j < gSize; j++)
    {
        cout << setw(4) << j << setw(12);

        if (smallestWeight[j] == DBL_MAX)
            cout << "INF";
        else
            cout << smallestWeight[j];

        cout << endl;
    }

    cout << endl;
}

int weightedGraphType::getSize() const
{
    return gSize;
}

weightedGraphType::weightedGraphType(int size)
    : graphType(size)
{
    weights = new double* [size];

    for (int i = 0; i < size; i++)
        weights[i] = new double[size];

    smallestWeight = new double[size];
}

weightedGraphType::~weightedGraphType()
{
    for (int i = 0; i < maxSize; i++)
        delete[] weights[i];

    delete[] weights;
    delete[] smallestWeight;
}

#endif