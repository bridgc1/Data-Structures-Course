#include "objPosDLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Doubly Linked List WITH DUMMY HEADER here.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosDLinkedList::objPosDLinkedList()
{
    listSize = 0;
    listHead = new DNode();
    listTail = new DNode();
    listHead->next = listTail; //initialize prev and next connections of head dummy node to tail dummy node
    listTail->prev = listHead;
    listTail->next = nullptr; //set the next ptr for listTail node to NULL
    persistHead = listHead; //initialized to dummy header
}

objPosDLinkedList::~objPosDLinkedList()
{
    persistHead = listHead->next;
    
    for (int i = 0; i < listSize; i++) {
        persistHead = persistHead->next;
        delete persistHead->prev;
    }
    delete listHead;
    delete listTail; 
}

int objPosDLinkedList::getSize()
{
    return listSize;
}

bool objPosDLinkedList::isEmpty()
{
    if (listHead->next == listTail)
    {
        return true;
    }
    return false;
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode* persistHead = new DNode();
    persistHead->data = thisPos; //create a temperary name for the new node
    persistHead->next = listHead->next;
    persistHead->prev = listHead;
    DNode* future_node = listHead->next;
    listHead->next = persistHead;
    future_node->prev = persistHead;
    
    listSize++; //increase size by 1
}

void objPosDLinkedList::insertTail(const objPos &thisPos)
{
   //add error catching lines here
    DNode* persistHead = new DNode();
    persistHead->data = thisPos;
    persistHead->next = listTail;
    persistHead->prev = listTail->prev;
    listTail->prev->next = persistHead;
    listTail->prev = persistHead;

    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
    if (index <= 0) //set default catch cases when out of practical index range
    {
        insertHead(thisPos); //includes size increment
    }
    else if (index >= listSize - 1)
    {
        insertTail(thisPos); //includes size increment
    }
    else
    {
        DNode* persistHead = new DNode();
        persistHead = listHead;

        for (int i = 0; i < index; i++)
        {
            persistHead = persistHead->next;
        }

        persistHead->data = thisPos;
        DNode* future_node = persistHead->prev->next; //create a temporary variable to store the address to the future node since the connection is being severed in the next line
        persistHead->prev->next = persistHead;
        persistHead->next = future_node;

        listSize++;
    }
}

objPos objPosDLinkedList::getHead() const
{
    if (listHead->next == listTail) {
        return objPos(-99,0,0,0,0); //represents invalid operation because no elements in list
    }
    else {
        return listHead->next->data;
    }
}

objPos objPosDLinkedList::getTail() const
{
    if (listHead->next == listTail) {
        return objPos(-99,0,0,0,0); //represents invalid operation because no elements in list
    }
    else {
        return listTail->prev->data;
    }
}

objPos objPosDLinkedList::get(int index) const
{
    if (listHead->next == listTail)
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
        DNode* persistHead = listHead->next; //start indexing from the first element (DOESN'T include the dummy header)
        for (int i = 0; i < index; i++)
        {
            persistHead = persistHead->next;
        }
        return persistHead->data;
    }
}

objPos objPosDLinkedList::getNext()
{
    persistHead = persistHead->next;
    if (persistHead == listTail)
    {
        resetReadPos();
        return objPos(-99,0,0,0,0);
    }
    else
    {
        return persistHead->data;
    }    
}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
    if (listHead->next != listTail) //execute the block only if the list is NOT empty
    {
        if (index < 0) {
            index = 0;
        }
        else if (index > listSize - 1)
        {
            index = listSize - 1;
        }
        
        DNode* persistHead = listHead->next; //start indexing from the first element (DOESN'T include dummy header position)
        for (int i = 0; i < index; i++)
        {
            persistHead = persistHead->next;
        }
        persistHead->data = thisPos;
        }
}


objPos objPosDLinkedList::removeHead()
{
    if (listHead->next == listTail)
    {
        return objPos(-99,0,0,0,0);
    }
    else
    {
        objPos persistHead_data = listHead->next->data; 
        
        DNode* tmp = listHead->next; //temporary storage for current element to be deleted

        listHead->next = tmp->next; //rearrange next pointer of previous node
        tmp->next->prev = listHead; //rearrange previous pointer of next node
        
        delete listHead->next; //delete the first node
        
        listSize--; //update the size

        return persistHead_data; //return the data of the first node
    }
}

objPos objPosDLinkedList::removeTail()
{
    if (listHead->next == listTail)
    {
        return objPos(-99,0,0,0,0);
    }
    else
    {
        objPos persistHead_data = listTail->prev->data; 

        DNode* tmp = listTail->prev;
        listTail->prev = tmp->prev; //set the previous pointer for the tail node to the address of the node before the last (to be deleted) node
        tmp->prev->next = listTail; //set the previous node's next pointer address to the tail node instead of the last (to be deleted) node

        delete tmp; //delete the last node

        listSize--; //update list size

        return persistHead_data;
    }
}

objPos objPosDLinkedList::remove(int index)
{
    if (listHead->next == listTail)
    {
        return objPos(-99,0,0,0,0); //return to indicate invalid operation
    }
    
    if (index <= 0) //set default catch cases when out of practical index range
    {
        return removeHead();
    }
    else if (index >= listSize - 1)
    {
        return removeTail();
    }
    else
    {
        DNode* persistHead = listHead->next; //start incrementing from the first element (DOESN'T include dummy header)
        for (int i = 0; i < index; i++)
        {
            persistHead = persistHead->next;
        }
        
        objPos temp_data = persistHead->data;

        persistHead->prev->next = persistHead->next; //set the previous node's NEXT pointer to the next node of the current node
        persistHead->next->prev = persistHead->prev; //set the previous node's NEXT pointer to the next node of the current node
        
        delete persistHead; //delete the current node

        listSize--; //update the list size

        return temp_data;
    }
}


void objPosDLinkedList::printList() const
{
    DNode* persistHead = listHead;
    cout << "Head: " << listHead << endl <<" Next with listHead: " << listHead->next << endl << " next with persistHead: " << persistHead->next << endl << endl;
    
    for (int i = 0; i < listSize; i++)
    {
        persistHead = persistHead->next;

        cout << "Element " << i;
        cout << " Address: " << persistHead << endl;
        cout << "Data: ";
        persistHead->data.printObjPos();
        cout << endl;
        cout << "Next: " << persistHead->next << endl;
        cout << "Prev: " << persistHead->prev << endl << endl;
    }
    cout << "Tail: " << listTail << endl << " Prev with listTail: " << listTail->prev << endl << " prev with persistHead: " << persistHead << endl << endl;
}


