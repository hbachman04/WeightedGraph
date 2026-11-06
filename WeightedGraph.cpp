#include <iostream>
#include <string>
#include "weightedGraph.h"

using namespace std;

int main()
{
    const int MAX_VERTICES = 100;
    weightedGraphType weightedGraph(MAX_VERTICES);

    string fileName;

    cout << "Enter input file name: ";
    cin >> fileName;

    weightedGraph.createWeightedGraph(fileName);

    if (weightedGraph.getSize() == 0)
        return 1;

    int sourceVertex;

    cout << "Enter the source vertex: ";
    cin >> sourceVertex;

    if (sourceVertex < 0 || sourceVertex >= weightedGraph.getSize())
    {
        cout << "Invalid source vertex. Please enter a vertex from 0 to "
            << weightedGraph.getSize() - 1 << "." << endl;
        return 1;
    }

    weightedGraph.shortestPath(sourceVertex);
    weightedGraph.printShortestDistance(sourceVertex);

    return 0;
}