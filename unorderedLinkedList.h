#ifndef H_unorderedLinkedList
#define H_unorderedLinkedList

#include "linkedList.h"

template <class Type>
class unorderedLinkedListType : public linkedListType<Type>
{
public:
    bool search(const Type& searchItem) const;
    void insertFirst(const Type& newItem);
    void insertLast(const Type& newItem);
    void deleteNode(const Type& deleteItem);
};

template <class Type>
bool unorderedLinkedListType<Type>::search(
    const Type& searchItem) const
{
    nodeType<Type>* current = this->first;

    while (current != nullptr)
    {
        if (current->info == searchItem)
            return true;

        current = current->link;
    }

    return false;
}

template <class Type>
void unorderedLinkedListType<Type>::insertFirst(
    const Type& newItem)
{
    nodeType<Type>* newNode = new nodeType<Type>;

    newNode->info = newItem;
    newNode->link = this->first;

    this->first = newNode;

    if (this->last == nullptr)
        this->last = newNode;

    this->count++;
}

template <class Type>
void unorderedLinkedListType<Type>::insertLast(
    const Type& newItem)
{
    nodeType<Type>* newNode = new nodeType<Type>;

    newNode->info = newItem;
    newNode->link = nullptr;

    if (this->first == nullptr)
    {
        this->first = newNode;
        this->last = newNode;
    }
    else
    {
        this->last->link = newNode;
        this->last = newNode;
    }

    this->count++;
}

template <class Type>
void unorderedLinkedListType<Type>::deleteNode(
    const Type& deleteItem)
{
    nodeType<Type>* current;
    nodeType<Type>* trailCurrent;

    bool found = false;

    if (this->first == nullptr)
        return;

    if (this->first->info == deleteItem)
    {
        current = this->first;
        this->first = this->first->link;

        this->count--;

        if (this->first == nullptr)
            this->last = nullptr;

        delete current;
    }
    else
    {
        trailCurrent = this->first;
        current = this->first->link;

        while (current != nullptr && !found)
        {
            if (current->info == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                current = current->link;
            }
        }

        if (found)
        {
            trailCurrent->link = current->link;

            if (this->last == current)
                this->last = trailCurrent;

            this->count--;

            delete current;
        }
    }
}

#endif