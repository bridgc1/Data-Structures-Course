#include "objPosStack.h"
#include "objPosSHLinkedList.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Available Data Members from objPosStack.h (Must Review)
//
//      objPosList* myList
//      
//  This is the polymorphic list pointer to the underlying List data structure to
//   support all Stack functionalities
//
//  You should use the provided objPosSHLinkedList as your main design param (Singly with Header)


objPosStack::objPosStack()
{
    myList = new objPosSHLinkedList();
}


objPosStack::~objPosStack()
{
    delete myList;
}


void objPosStack::populateRandomElements(int size)
{
    // This function generates the number of randomly generated objPos instances with uninitialized
    //  x-y coordinate on the Stack, then sort them in ascending order using the digit of 10
    //  of the **number** field in objPos instances.

    // Implementation done.  You'd have to implement the following two private helper functions above.
    srand(time(NULL));
    generateObjects(size);
    sortByTenScoreBS();   // bubble sort
}




// private helper function
void objPosStack::generateObjects(int count)
{
    // Generate and pushes individual objPos isntances with randomly generated Prefix, Number, and Symbol.
    // The total number of generated instances is capped by input variable **count**.
    int prefix;
    for (int i = 0; i < count; i++) //iterate for count times
    {
        do
        {
            prefix = 65 + rand() % 58;
            
        } while (prefix < 97 && prefix > 90);

        char letter = (char)prefix; //typecast the random integers
        int number = rand(); // note that .setNum(int) already applies mod 100 for passed in integer
        char symbol = '*';

        objPos data; //create object of objPos type to hold randomly generated values
        data.setPF(letter); //use the setter methods to set the randomly generated values to data
        data.setNum(number);
        data.setSym(symbol);

        myList->insertHead(data); //insert the generated node
    }

    // 1. Generate Prefix A-Z and a-z.  Alphabetic characters only.
    // 2. Generate Number [0, 99]
    // 3. Leave Symbol as *
    // Push every randomly generately objPos into the Stack.

}


// private helper function
void objPosStack::sortByTenScoreBS()
{
    bool unordered;
    do
    {
        unordered = false; //reset to assume list is in proper order
        for (int i = 0; i < myList->getSize()-1; i++) //iterate for the list size
        {
            if ((myList->get(i).getNum() / 10) > (myList->get(i+1).getNum() / 10)) //if the previous element has a larger number field than the next element
            {
            
            objPos temp = myList->get(i);

            myList->set(myList->get(i+1),i);
            myList->set(temp, i+1); //swap the objPos contents of the nodes
            unordered = true;
            
            }
        }
        

    } while (unordered);
    
    // Use BUBBLE or SELECTION SORT to sort all the objPos instances in the Stack in ascending order using the doigit of 10
    //  of the **number** field of objPos.

    // You can use the relevant insertion, removal, getter, and setter methods from the objPosSHLinkedList interface
    //  to complete the sorting operations.

}




void objPosStack::push(const objPos &thisPos) const
{
    myList->insertHead(thisPos);

}

objPos objPosStack::pop()
{
    if (myList->getSize() == 0) //error case handling for empty list
    {
        return objPos(-99,0,0,0,0);
    }

    objPos data = myList->getHead(); //set temporary variable for data of head element
    myList->removeHead(); //delete head element

    return data;
   
}

objPos objPosStack::top()
{
    if (myList->getSize() == 0)
    {
        return objPos(-99, 0, 0, 0, 0);
    }
    return myList->getHead();
    
}

int objPosStack::size()
{
    return myList->getSize();
}

void objPosStack::printMe()
{
    myList->printList();   
}