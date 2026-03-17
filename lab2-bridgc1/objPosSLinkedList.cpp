#include "objPosSLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Singly Linked List WITHOUT DUMMY HEADER.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosSLinkedList::objPosSLinkedList()
{
    listSize = 0;
    listHead = nullptr;
}

objPosSLinkedList::~objPosSLinkedList()
{
    while (listHead != nullptr)
    {
        SNode* tmp = listHead; //temporary storage for pointer to listHead
        listHead = listHead->next; //iterate through entire list
        delete tmp; //delete listHead
    }
}

int objPosSLinkedList::getSize()
{
    return listSize;
}

bool objPosSLinkedList::isEmpty()
{
   if (listHead == nullptr)
   {
        return true; //return true if list is empty aka listHead is empty
   }
   else return false;
}

void objPosSLinkedList::insertHead(const objPos &thisPos)
{
    SNode* tmp = new SNode();
    tmp->data = thisPos; //input data 

    if (listSize == 0) //if list is empty, set the list head as the current element
    {
        tmp->next = nullptr;
        listHead = tmp;
    }
    else //if list is NOT empty
    {
        tmp->next = listHead; //set the current element's next pointer to the current head
        listHead = tmp; //set the new head location to be the inserted element
    }
    persistHead = listHead;
    
    listSize++; //update the list size
}

void objPosSLinkedList::insertTail(const objPos &thisPos)
{
    SNode* tmp = new SNode();
    tmp->data = thisPos;

    if (listSize == 0)
    {
        listHead = tmp;
        tmp->next = nullptr;
    }
    else{
        persistHead = listHead; //set the current pointer to the list head
        while (persistHead->next != nullptr)
        {
            persistHead = persistHead->next; //iterate through the list until reaching the last element
        }
        persistHead->next = tmp; //set the last element to point next to the pointer for the element being inserted
        tmp->next = nullptr; //set the inserted element to point to null (at the end of the list)
    }

    listSize++; //update list size
}

void objPosSLinkedList::insert(const objPos &thisPos, int index)
{
    if (index < 0) //set default catch cases when out of practical index range
    {
        insertHead(thisPos); //includes size increment
    }
    else if (index > listSize-1)
    {
        insertTail(thisPos); //includes size increment
    }
    else
    {
        SNode* tmp = new SNode();
        SNode* persistHead = listHead;
        for (int i = 0; i < index - 1; i++)
        {
            persistHead = persistHead->next; // last iteration at node before indexed element
        }

        tmp->next = persistHead->next; //link next pointer of inserted node to the current node at that index 
        persistHead->next = tmp; //set node before index to point to inserted node

        listSize++; //update list size
    }
}

objPos objPosSLinkedList::getHead() const
{
    if (listSize == 0)
    {
        return objPos(-99,0,0,0,0); //return invalid objPos
    }
    return listHead->data;
}

objPos objPosSLinkedList::getTail() const
{
    if (listSize == 0)
    {
        return objPos(-99,0,0,0,0); //return invalid objPos data if list is empty
    }
    SNode* persistHead = listHead;
    while (persistHead->next != nullptr)
    {
        persistHead = persistHead->next;
    }
    return persistHead->data;
}

objPos objPosSLinkedList::get(int index) const
{
    if (listHead == nullptr)
    {
        return objPos(-99,0,0,0,0); //return to indicate invalid operation
    }
    if (index <= 0) //set default catch cases when out of practical index range
    {
        return getHead();
    }
    else if (index >= listSize - 1)
    {
        return getTail();
    }
    else
    {
        SNode* persistHead = listHead; //start indexing from the first element  **DIFFERENCE WITH DUMMY DLINKED LIST: start indexing AT FIRST NODE
        for (int i = 0; i < index; i++)
        {
            persistHead = persistHead->next;
        }
        return persistHead->data;
    }
}

objPos objPosSLinkedList::getNext()
{
    if (persistHead != nullptr) //if initialized and thus at least one node in list
    {
        objPos tmp_data = persistHead->data; //temporarily save data for current node before traversing to the next node
        persistHead = persistHead->next;
        return tmp_data;
    }
    
    resetReadPos(); //if at the end of the list or list is empty then reset persistHead to header node (= nullptr in empty case)
    return objPos(-99,0,0,0,0); //returns indicator for invalid operation (i..e end of list or empty list)
    
}

void objPosSLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosSLinkedList::set(const objPos &thisPos, int index)
{
    if (listSize != 0)
    {
        if (index < 0) //set valid extremity index values for invalid indexes
        {
            index = 0;
        }
        else if (index > listSize - 1)
        {
            index = listSize - 1;
        }
        
        persistHead = listHead;
        for (int i = 0; i < index; i++)
        {
            persistHead = persistHead->next;
        }
        persistHead->data = thisPos;
    }    
}


objPos objPosSLinkedList::removeHead()
{
    if (listSize > 0) //if the list contains at least one node
    {
        objPos tmp_data = listHead->data;
        SNode* tmp = listHead->next; //access element after header (why this specific conditional statement is necessary)
        delete listHead;
        listHead = tmp;
        listSize--;
        return tmp_data;
    }

    return objPos(-99,0,0,0,0); //return invalid operation
}

objPos objPosSLinkedList::removeTail()
{
    if (listSize == 1)
    {
        return removeHead(); //if only one element remove that element
    }
    else if (listSize > 1) //else if greater than one --> required since accessing two future nodes (error handling)
    {
        persistHead = listHead;
        while (persistHead->next->next != nullptr)
        {
            persistHead = persistHead->next; //iterate to the second last element
        }
        objPos tmp_data = persistHead->next->data;
        delete persistHead->next; //delete the pointer of the next element
        persistHead->next = nullptr; //set the next pointer of the current element to null (becomes tail node)
        listSize--;
        return tmp_data;
    }
    return objPos(-99,0,0,0,0); //signifies invalid operation
}

objPos objPosSLinkedList::remove(int index)
{
    if (listSize != 0)
    {
        if (index <= 0)
        {
            return removeHead();
        }
        else if (index >= listSize - 1)
        {
            return removeTail();
        }
        else
        {
            persistHead = listHead;
            for (int i = 0; i < index - 1; i++)
            {
                persistHead = persistHead->next;
            }

            objPos tmp_data = persistHead->next->data; //temperary storage for indexed element's data
            if (persistHead->next->next == nullptr)
            {
                delete persistHead->next; //delete last element (after indexed element)
                persistHead->next = nullptr; //point the node previous to the indexed element to nullptr instead so it becomes the new last element
            }
            else {
                SNode* tmp = persistHead->next->next; //temporary storage for pointer to node after indexed element
                delete persistHead->next; //remove indexed element
                persistHead->next = tmp; //set node before indexed element to point to element after indexed element
            }
            
            listSize--; //update list size

            return tmp_data; //return data for deleted node
        }
    }

    return objPos(-99,0,0,0,0); //signifies invalid operation
    
}

void objPosSLinkedList::printList() const //check over since pasted
{
    if (listSize != 0)
    {
        int i = 0;
        SNode* persistHead = listHead;
        cout << "Head: " << listHead << endl <<" Next with listHead: " << listHead->next << endl << " next with persistHead: " << persistHead->next << endl << endl;

        while (persistHead->next != nullptr)
        {
            persistHead = persistHead->next;

            cout << "Element " << i;
            cout << " Address: " << persistHead << endl;
            cout << "Data: ";
            persistHead->data.printObjPos();
            cout << endl;
            cout << "Next: " << persistHead->next << endl;
            i++;
        }
    }
    
}


