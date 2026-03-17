#include "ItemBin.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

ItemBin::ItemBin(GameMechs* gm)
{
    gmRef = gm;
    boardRef = gmRef->getBoardRef();  
    myItem = new objPos(12, 12, 32, 'A', '*');  

    srand(time(NULL));    
}

ItemBin::~ItemBin()
{
    delete myItem;
}

void ItemBin::drawItem()
{
    int x = myItem->getX();    
    int y = myItem->getY();     
    char num[2];  // convert number to displayable chars     
    DigitToChar(num);    

    boardRef[y][x] = myItem->getSym();    
    boardRef[y-1][x-1] = myItem->getPF();    
    boardRef[y-1][x] = num[0];    
    boardRef[y-1][x+1] = num[1];    
}      

void ItemBin::undrawItem()
{
    int x = myItem->getX();   
    int y = myItem->getY();

    boardRef[y][x] = ' ';
    boardRef[y-1][x-1] = ' ';
    boardRef[y-1][x] = ' ';
    boardRef[y-1][x+1] = ' ';
}

void ItemBin::DigitToChar(char result[])
{
    int number = myItem->getNum();     
    result[0] = (number / 10) + '0';      
    result[1] = (number % 10) + '0';    
}    


void ItemBin::generateItem()
{
    // Step 1: Get Player Ref from GameMech for Player pos
    Player** plList = gmRef->getPlayerListRef();          
    objPosList *playerPos = plList[0]->getPlayerPos();    

    //int bitVec[gmRef->getBoardSizeX()][gmRef->getBoardSizeY()]= {0};

    // to prevent stack overflow
    int xsize = gmRef->getBoardSizeX();
    int ysize = gmRef->getBoardSizeY();
    int** bitVec = new int*[xsize];
    for(int i = 0; i < xsize; i++)     // Dr. Chen said to assume a board size of n x n
    {
        bitVec[i] = new int[ysize];
        for(int j = 0; j < ysize; j++)     // nested for loop --> theta(n^2)
            bitVec[i][j] = 0;
    }
       


    int playerLength = playerPos->getSize();    // theta(1)

    objPos target;  
    playerPos->resetReadPos();     // theta(1)

    for(int i = 0; i < playerLength; i++)    // theta(n)
    {
        target = playerPos->getNext();  
        bitVec[target.getX()][target.getY()] = 1;       
    }    

    int randCandidateX = 0;
    int randCandidateY = 0;
    int randCandidate = 0;

    // Step 2: Generate another food object
    // Coordinate Generation
    // x [2, BoardX-3]
    // y [2, BoardY-3]   

    do
    {
        randCandidateX = rand() % (gmRef->getBoardSizeX() - 4) + 2;
        randCandidateY = rand() % (gmRef->getBoardSizeY() - 4) + 2;
    } while(bitVec[randCandidateX][randCandidateY] != 0);       // omega(1) on its own but with nested for loop is omega(n^2)
    //possibility that a position vector
    //corresponding to an empty space
    //is never randomized thus omega n^2
    //(bounded n^2 due to nested for loop above)
    

    undrawItem();  //theta(constant)

    myItem->setX(randCandidateX);  // theta(constant)
    myItem->setY(randCandidateY);     

    // Prefix Generation
    // PF   [a-z, A-Z]
    randCandidate = rand() % 26 + 'A';  // 26 alpabets          //theta(constant)
    if(rand() % 2) randCandidate += 32; // randomly lowercased 
    myItem->setPF((char)randCandidate); 

    // Number Generation
    // Number [00, 99]
    myItem->setNum(rand() % 100);    // theta(constant)

    drawItem();  //theta(constant)

    for(int i = 0; i < xsize; i++)    //theta(n)
        delete[] bitVec[i];
    delete[] bitVec;
}


objPos ItemBin::getItem()
{
    objPos temp(myItem->getX(), myItem->getY(), myItem->getNum(), myItem->getPF(), myItem->getSym());
    // constructor     
    return temp;  // copy constructor     
}   
