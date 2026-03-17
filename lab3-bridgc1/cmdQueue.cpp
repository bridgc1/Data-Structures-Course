#include "cmdQueue.h"

#include <iostream>
using namespace std;

// Available Data Members from cmdQueue.h

// You must implement the array-based circular queue as discussed in class

// You must NOT use any existing data structures such as Lists to design the queue.


cmdQueue::cmdQueue()
{
    capacity = DEFAULT_CAPACITY;

    queue = new char[capacity];
    size = 0;
    front = 0;
    end = 0;

}

cmdQueue::cmdQueue(int cap)
{
    capacity = cap;

    queue = new char[capacity];
    size = 0;
    front = 0;
    end = 0;
}

cmdQueue::~cmdQueue()
{
    delete[] queue; //delete entire array
    
}

void cmdQueue::enqueue(char thisCmd)
{
    if (size < capacity)
    {

        front = (front - 1 + capacity) % capacity;
        queue[front] = thisCmd;

        size++;
    }

}

char cmdQueue::dequeue()
{
    if (size > 0)
    {
        char element = queue[(end-1+capacity)%capacity]; //temporary storage for character
        queue[(end-1+capacity)%capacity] = 0; //set last element that is dequeued to null
        end = (end - 1 + capacity) % capacity;    

        size--;
        return element;
    }
    else
    {
        return '!'; //error message (attempt to access empty queue)
    }
}

int cmdQueue::getSize() const
{
    if (front <= end)
    {
        return (end-front);
    }
    else{
        return (capacity+end-front);
    }
    
}

void cmdQueue::clearQueue()
{
    for (int i = 0; i < size; i++)
    {
        queue[(front+i)%capacity] = 0;
    }
    front = 0; end = 0; size = 0;
}

void cmdQueue::printMe() const
{
    for (int i = 0; i < size; i++)
    {
        cout << "Item " << (front+i)%capacity << ":    " << queue[(front+i)%capacity];
        
    }
    // NOT GRADED
    //  Print the contents of the Queue
    
    // IMPORTANT: USE THIS METHOD FOR DEBUGGING!!!
}