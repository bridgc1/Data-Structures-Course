#include "objPosDoubleHashing.h"
// #include "MacUILib.h"

#include <iostream>
using namespace std;

objPosDoubleHashing::objPosDoubleHashing()
{
    // do you need anything here?     
}

objPosDoubleHashing::objPosDoubleHashing(int size) : objPosHashTable(size)
{
    // do you need to modify anything here?
}

objPosDoubleHashing::~objPosDoubleHashing()
{
    // do you need anything here? 
}

int objPosDoubleHashing::calculateSecondaryHashing(int input) const
{
    int total = 0;

    while (input > 0)
    {
        total += input % 10;
        input /= 10;
    }

    return (5 - (total % 5));

    // Secondary Hashing Function

    // Formula : sum of all digits of the first hashing index mod 5.

    // Ex. Hashing Index = 36, then Secondary Hashing Index = (3 + 6) % 5 = 4
}

bool objPosDoubleHashing::insert(const objPos &thisPos)
{
    int init_index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int index = init_index;
    int probe = 0;

    while (probe < MAX_PROBING_COUNT) //no need to account for max probing count since linear checking
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
        probe++;
        index = (init_index + probe*calculateSecondaryHashing(init_index)) % tableSize;
    }
    return false;

    // Insert thisPos into the Hash Table (if not already inserted) using Double Hashing

    // When inserting, using Symbol as a way to check if the table entry is occupied or free
    //    Symbol = 0 (FREE),   Symbol = 'v' (Occupied)
}

bool objPosDoubleHashing::remove(const objPos &thisPos)
{
    int init_index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int index = init_index;
    int probe = 0;
    
    for (int probe = 0; probe < MAX_PROBING_COUNT; probe++) 
    {
        if ((myHashTable[index].getPF() == thisPos.getPF()) && (myHashTable[index].getNum() == thisPos.getNum()) && (myHashTable[index].getSym() == 'v'))
        {
            myHashTable[index].setSym(0);
            return true;
        }
        
        index = (init_index + probe*calculateSecondaryHashing(init_index)) % tableSize;
    }
    return false;

    // Remove thisPos from the Hash Table using Double Hashing

    // If found in the table, apply lazy deletion by setting Symbol = 0 (free), and return true
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.    
}

bool objPosDoubleHashing::isInTable(const objPos &thisPos) const
{
    int init_index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int index = init_index;
    int probe = 0;
    
    while (probe < MAX_PROBING_COUNT)
    {
        if ((myHashTable[index].getPF() == thisPos.getPF()) && (myHashTable[index].getNum() == thisPos.getNum()) && myHashTable[index].getSym() == 'v')
        {
            return true; // object already in the hash table distinguished by its prefix
        }
        probe++;
        index = (init_index + probe*calculateSecondaryHashing(init_index)) % tableSize;
    }
    return false;

    // Check if thisPos is in the Hash Table using Double Hashing

    // If found in the table, return true
        // Remember, finding the match is not enough.  The entry has to be VALID (symbol = 'v').
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.    
}