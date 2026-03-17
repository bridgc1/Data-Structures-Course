#include "objPosLinearHashing.h"

#include <iostream>
using namespace std;

objPosLinearHashing::objPosLinearHashing()
{
    // do you need anything here?     
}

objPosLinearHashing::objPosLinearHashing(int size) : objPosHashTable(size)
{
    // do you need to modify anything here?
}

objPosLinearHashing::~objPosLinearHashing()
{
    // do you need anything here?     
}

bool objPosLinearHashing::insert(const objPos &thisPos)
{
    int index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int probe = 0;

    while (probe < tableSize) //no need to account for max probing count since linear checking
    {
        if ((myHashTable[index].getPF() == thisPos.getPF()) && (myHashTable[index].getNum() == thisPos.getNum()) && myHashTable[index].getSym() == 'v')
        {
            return false; // object already in the hash table distinguished by its prefix and number
        }

        if (myHashTable[index].getSym() == 0)
        {
            myHashTable[index] = thisPos;
            myHashTable[index].setSym('v');
            return true;
        }
        index = (index + 1) % tableSize;
        probe++;
    }
    return false;
    // Insert thisPos into the Hash Table (if not already inserted) using Linear Probing

    // When inserting, using Symbol as a way to check if the table entry is occupied or free
    //    Symbol = 0 (FREE),   Symbol = 'v' (Occupied)
}

bool objPosLinearHashing::remove(const objPos &thisPos)
{
    int index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    
    for (int probe = 0; probe < tableSize; probe++) 
    {
        if ((myHashTable[index].getPF() == thisPos.getPF()) && (myHashTable[index].getNum() == thisPos.getNum()) && (myHashTable[index].getSym() == 'v'))
        {
            myHashTable[index].setSym(0);
            return true;
        }
        
        index = (index + 1) % tableSize;
    }
    return false;
    // Insert thisP
    // Remove thisPos from the Hash Table using Linear Probing

    // If found in the table, apply lazy deletion by setting Symbol = 0 (free), and return true
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.    
}

bool objPosLinearHashing::isInTable(const objPos &thisPos) const
{
    // Check if thisPos is in the Hash Table using Linear Probing
    
    int index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int probe = 0;
    while (probe < MAX_PROBING_COUNT && probe < tableSize)
    {
        if ((myHashTable[index].getPF() == thisPos.getPF()) && (myHashTable[index].getNum() == thisPos.getNum()) && myHashTable[index].getSym() == 'v')
        {
            return true; // object already in the hash table distinguished by its prefix
        }
        index = (index + 1) % tableSize;
        probe++;
    }
    return false;

    // If found in the table, return true
        // Remember, finding the match is not enough.  The entry has to be VALID (symbol = 'v').
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.    
}