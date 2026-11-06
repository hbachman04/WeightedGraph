#ifndef H_linkedList
#define H_linkedList

#include <iostream>
#include <cassert>

using namespace std;

template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type>* link;
};

template <class Type>
class linkedListIterator
{
public:
    linkedListIterator()
    {
        current = nullptr;
    }

    linkedListIterator(nodeType<Type>* ptr)
    {
        current = ptr;
    }

    Type operator*()
    {
        return current->info;
    }

    linkedListIterator<Type> operator++()
    {
        current = current->link;
        return *this;
    }

    bool operator==(const linkedListIterator<Type>& right) const
    {
        return current == right.current;
    }

    bool operator!=(const linkedListIterator<Type>& right) const
    {
        return current != right.current;
    }

private:
    nodeType<Type>* current;
};

template <class Type>
class linkedListType
{
public:
    const linkedListType<Type>& operator=
        (const linkedListType<Type>&);

    void initializeList();
    bool isEmptyList() const;
    int length() const;
    void destroyList();

    Type front() const;
    Type back() const;

    virtual bool search(const Type& searchItem) const = 0;
    virtual void insertFirst(const Type& newItem) = 0;
    virtual void insertLast(const Type& newItem) = 0;
    virtual void deleteNode(const Type& deleteItem) = 0;

    linkedListIterator<Type> begin();
    linkedListIterator<Type> end();

    linkedListType();
    linkedListType(const linkedListType<Type>& otherList);
    virtual ~linkedListType();

protected:
    int count;
    nodeType<Type>* first;
    nodeType<Type>* last;

private:
    void copyList(const linkedListType<Type>& otherList);
};

template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return (first == nullptr);
}

template <class Type>
linkedListType<Type>::linkedListType()
{
    first = nullptr;
    last = nullptr;
    count = 0;
}

template <class Type>
void linkedListType<Type>::destroyList()
{
    nodeType<Type>* temp;

    while (first != nullptr)
    {
        temp = first;
        first = first->link;
        delete temp;
    }

    last = nullptr;
    count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
    destroyList();
}

template <class Type>
Type linkedListType<Type>::front() const
{
    assert(first != nullptr);
    return first->info;
}

template <class Type>
Type linkedListType<Type>::back() const
{
    assert(last != nullptr);
    return last->info;
}

template <class Type>
int linkedListType<Type>::length() const
{
    return count;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
    return linkedListIterator<Type>(first);
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
    return linkedListIterator<Type>(nullptr);
}

template <class Type>
void linkedListType<Type>::copyList(
    const linkedListType<Type>& otherList)
{
    nodeType<Type>* current;

    if (first != nullptr)
        destroyList();

    if (otherList.first == nullptr)
    {
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.first;

        count = otherList.count;

        first = new nodeType<Type>;
        first->info = current->info;
        first->link = nullptr;

        last = first;

        current = current->link;

        while (current != nullptr)
        {
            nodeType<Type>* newNode = new nodeType<Type>;

            newNode->info = current->info;
            newNode->link = nullptr;

            last->link = newNode;
            last = newNode;

            current = current->link;
        }
    }
}

template <class Type>
linkedListType<Type>::linkedListType(
    const linkedListType<Type>& otherList)
{
    first = nullptr;
    last = nullptr;
    count = 0;

    copyList(otherList);
}

template <class Type>
linkedListType<Type>::~linkedListType()
{
    destroyList();
}

template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(
    const linkedListType<Type>& otherList)
{
    if (this != &otherList)
        copyList(otherList);

    return *this;
}

#endif