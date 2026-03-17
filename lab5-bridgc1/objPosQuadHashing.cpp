#include "objPosQuadHashing.h"

#include <iostream>
using namespace std;

objPosQuadHashing::objPosQuadHashing()
{
    // do you need anything here?     
}

objPosQuadHashing::objPosQuadHashing(int size) : objPosHashTable(size)
{
    // do you need to modify anything here?
}

objPosQuadHashing::~objPosQuadHashing()
{
    // do you need anything here?     
}

bool objPosQuadHashing::insert(const objPos &thisPos)
{
    int init_index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int index = init_index;
    int probe = 0;

    while (probe < MAX_PROBING_COUNT)
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
        index = (init_index + probe*probe) % tableSize;
    }
    return false;

    // Insert thisPos into the Hash Table (if not already inserted) using Quadratic Probing

    // When inserting, using Symbol as a way to check if the table entry is occupied or free
    //    Symbol = 0 (FREE),   Symbol = 'v' (Occupied)
}

bool objPosQuadHashing::remove(const objPos &thisPos)  // lazy delete 
{

    int init_index = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int index = init_index;
    
    for (int probe = 1; probe < MAX_PROBING_COUNT; probe++) 
    {
        if ((myHashTable[index].getPF() == thisPos.getPF()) && (myHashTable[index].getNum() == thisPos.getNum()) && (myHashTable[index].getSym() == 'v'))
        {
            myHashTable[index].setSym(0);
            return true;
        }
        index = (init_index + probe*probe) % tableSize;
    }
    return false;
    // Remove thisPos from the Hash Table using Quadratic Probing

    // If found in the table, apply lazy deletion by setting Symbol = 0 (free), and return true
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily.
}

bool objPosQuadHashing::isInTable(const objPos &thisPos) const
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
        index = (init_index + probe*probe) % tableSize;
    }
    return false;

    // Check if thisPos is in the Hash Table using Quadratic Probing

    // If found in the table, return true
        // Remember, finding the match is not enough.  The entry has to be VALID (symbol = 'v').
    // If not found in the table, return false

    // You need to think carefully about what conditions will end the probing
    // During debugging, you may use MAX_PROBING_COUNT defined in objPosHash.h as a hard limit to the number of probes 
    // to be carried out.  This hard limit is not to fix the bug, but only to help you debugger more easily. 
}