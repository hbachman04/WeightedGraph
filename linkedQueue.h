#ifndef H_linkedQueue
#define H_linkedQueue

#include <iostream>
#include <cassert>
#include "queueADT.h"
#include "linkedList.h"

using namespace std;

template <class Type>
class linkedQueueType : public queueADT<Type>
{
public:
    const linkedQueueType<Type>& operator=(
        const linkedQueueType<Type>&);

    bool isEmptyQueue() const;
    bool isFullQueue() const;

    void initializeQueue();

    Type front() const;
    Type back() const;

    void addQueue(const Type& queueElement);
    void deleteQueue();

    linkedQueueType();
    linkedQueueType(const linkedQueueType<Type>& otherQueue);
    ~linkedQueueType();

private:
    nodeType<Type>* queueFront;
    nodeType<Type>* queueRear;
};

template <class Type>
linkedQueueType<Type>::linkedQueueType()
{
    queueFront = nullptr;
    queueRear = nullptr;
}

template <class Type>
bool linkedQueueType<Type>::isEmptyQueue() const
{
    return (queueFront == nullptr);
}

template <class Type>
bool linkedQueueType<Type>::isFullQueue() const
{
    return false;
}

template <class Type>
void linkedQueueType<Type>::initializeQueue()
{
    nodeType<Type>* temp;

    while (queueFront != nullptr)
    {
        temp = queueFront;
        queueFront = queueFront->link;

        delete temp;
    }

    queueRear = nullptr;
}

template <class Type>
void linkedQueueType<Type>::addQueue(
    const Type& newElement)
{
    nodeType<Type>* newNode = new nodeType<Type>;

    newNode->info = newElement;
    newNode->link = nullptr;

    if (queueFront == nullptr)
    {
        queueFront = newNode;
        queueRear = newNode;
    }
    else
    {
        queueRear->link = newNode;
        queueRear = newNode;
    }
}

template <class Type>
Type linkedQueueType<Type>::front() const
{
    assert(queueFront != nullptr);

    return queueFront->info;
}

template <class Type>
Type linkedQueueType<Type>::back() const
{
    assert(queueRear != nullptr);

    return queueRear->info;
}

template <class Type>
void linkedQueueType<Type>::deleteQueue()
{
    if (!isEmptyQueue())
    {
        nodeType<Type>* temp = queueFront;

        queueFront = queueFront->link;

        delete temp;

        if (queueFront == nullptr)
            queueRear = nullptr;
    }
    else
    {
        cout << "Cannot remove from an empty queue."
            << endl;
    }
}

template <class Type>
linkedQueueType<Type>::~linkedQueueType()
{
    initializeQueue();
}

template <class Type>
const linkedQueueType<Type>&
linkedQueueType<Type>::operator=(
    const linkedQueueType<Type>& otherQueue)
{
    if (this != &otherQueue)
    {
        initializeQueue();

        nodeType<Type>* current = otherQueue.queueFront;

        while (current != nullptr)
        {
            addQueue(current->info);
            current = current->link;
        }
    }

    return *this;
}

template <class Type>
linkedQueueType<Type>::linkedQueueType(
    const linkedQueueType<Type>& otherQueue)
{
    queueFront = nullptr;
    queueRear = nullptr;

    nodeType<Type>* current = otherQueue.queueFront;

    while (current != nullptr)
    {
        addQueue(current->info);
        current = current->link;
    }
}

#endif