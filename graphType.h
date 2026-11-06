#ifndef H_graphType
#define H_graphType

#include <iostream>
#include "unorderedLinkedList.h"

using namespace std;

class graphType
{
public:
    bool isEmpty() const;
    void clearGraph();
    void printGraph() const;

    graphType(int size = 0);
    virtual ~graphType();

protected:
    int maxSize;
    int gSize;

    unorderedLinkedListType<int>* graph;
};

graphType::graphType(int size)
{
    if (size <= 0)
        maxSize = 100;
    else
        maxSize = size;

    gSize = 0;

    graph = new unorderedLinkedListType<int>[maxSize];
}

graphType::~graphType()
{
    delete[] graph;
}

bool graphType::isEmpty() const
{
    return (gSize == 0);
}

void graphType::clearGraph()
{
    for (int i = 0; i < gSize; i++)
        graph[i].initializeList();

    gSize = 0;
}

void graphType::printGraph() const
{
    for (int i = 0; i < gSize; i++)
    {
        cout << i << ": ";

        linkedListIterator<int> it = graph[i].begin();

        while (it != graph[i].end())
        {
            cout << *it << " ";
            ++it;
        }

        cout << endl;
    }
}

#endif