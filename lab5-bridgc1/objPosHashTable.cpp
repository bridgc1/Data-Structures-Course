#include <iostream>
#include "objPosHashTable.h"

// Provided Code for Model Code Integration
////////////////////////////////////////////////

// uncomment this line when integrating with model code
#include "./Lab5-Model/inc/MacUILib.h"

using namespace std;

objPosHashTable::objPosHashTable()
{
    tableSize = TABLE_SIZE;
    myHashTable = new objPos[TABLE_SIZE];
    for (int i = 0; i < tableSize; i++)
    {
        myHashTable[i] = objPos(0, 0, 0, '\0', '\0');
    }
    // create the hash table with default size (TABLE_SIZE)

    // By default, all elements in the table should be initialized to:
    //  x = 0, y = 0, prefix = '\0' (0), number = 0, symbol = '\0' (0)
}

objPosHashTable::objPosHashTable(int size)
{
    tableSize = size;
    myHashTable = new objPos[size];
    for (int i = 0; i < tableSize; i++)
    {
        myHashTable[i] = objPos(0, 0, 0, '\0', '\0');
    }
    // create the hash table with the custom size (size)

    // By default, all elements in the table should be initialized to:
    //  x = 0, y = 0, prefix = '\0' (0), number = 0, symbol = '\0' (0)
}

objPosHashTable::~objPosHashTable()
{
    delete[] myHashTable;
    // remove the hash table
}

int objPosHashTable::calculateHashing(int prefix, int number) const
{
    // can divide by 100 to get the truncated hundreds value (first digit as an integer)
    // divide by 10 to get tens value and modulus 10 (second digit as integer)
    // use modulus 100 to get the remainder (third digit as an integer)
    int prefix_total = 0;

    while (prefix > 0)
    {
        prefix_total += prefix%10;
        prefix = prefix / 10;
    }

    return (prefix_total + (number/10 + number%10)) % tableSize;
    // // calculate the hash index using the prefix and number.

    // Formula: Add all digits of the number and the integer value of the ASCII prefix.

    // Ex. prefix = 'A'(65), number = 37
    //     return value = 6 + 5 + 3 + 7 = 21
}

double objPosHashTable::getLambda() const
{
    int count = 0;
    for (int i = 0; i < tableSize; i++)
    {
        if (myHashTable[i].getSym() != '\0') //if prefix is null, this is an indicator that this element in the hash array is not occupied
        {
            count++;
        }
    }
    return (double)count/(double)tableSize;
    // calculate the load factor of the hash table
}

void objPosHashTable::printMe() const
{
    // Provided for verbose mode in Test.cpp
    // comment the entire for-loop out when integrating with the model code.
    // for(int i = 0; i < tableSize; i++)
    // {
    //     cout << "[" << i << "]  " << myHashTable[i].getPF() << myHashTable[i].getNum() << " " << myHashTable[i].getSym() << endl;     
    // }



    // Provided Code for Model Code Integration
    ////////////////////////////////////////////////

    // uncomment the following lines when integrating with model code

    MacUILib_printf("[ ");
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(myHashTable[i].getSym() != 0)
            MacUILib_printf("%c%d ", myHashTable[i].getPF(), myHashTable[i].getNum());     
    }
    MacUILib_printf("] L=%.2f", getLambda());

    // You will also need to #include "MacUILib.h" when integrating with the model code.
}