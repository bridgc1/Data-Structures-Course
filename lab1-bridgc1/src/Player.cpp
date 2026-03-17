#include "Player.h"
#include "objPosArrayList.h"
//#include "objPosDLinkedList.h"

#include <iostream>
using namespace std;

#define TEST_LENGTH 1000

Player::Player(int x, int y, char symbol, GameMechs* gm, ItemBin* bin)
{
   
    // Choose the list type for Lab 2
    myPos = new objPosArrayList();       

    // turn false for performance estimation in Lab 2
    killable = true;  
    
    myPos->insertHead(objPos(x, y, -1, 0, symbol));
       
    gmRef = gm;
    boardRef = gmRef->getBoardRef();
    binRef = bin;

    myDir = STOP;
    myScore = 0;

    gmRef->addPlayer(this);
}

Player::~Player()
{
    delete myPos;
}


void Player::updatePlayerFSM()  // private
{
    char cmd = gmRef->getCMD();   
    switch(cmd)   
    {
        case 'w':
        case 'W':
            if(myDir != DOWN) myDir = UP;   
            break;

        case 's':
        case 'S':
            if(myDir != UP) myDir = DOWN;    
            break;

        case 'a':
        case 'A':
            if(myDir != RIGHT) myDir = LEFT;    
            break;

        case 'd':
        case 'D':
            if(myDir != LEFT) myDir = RIGHT;    
            break;

        default:
            break;    
    }
}   

void Player::movePlayer()
{    
    updatePlayerFSM();   //1
    if(myDir == STOP) return;    // if true, theta(1)

    undrawPlayer();  //theta(n)
    
    objPos currHeadPos = myPos->getHead();   //1
    int inX = currHeadPos.getX();  //1
    int inY = currHeadPos.getY();   //1
        
    switch(myDir) // constant
    {
        case UP:            
            if(--inY < 1)  
                inY = gmRef->getBoardSizeY() - 2;  //1...
            break;

        case DOWN:
            if(++inY > (gmRef->getBoardSizeY() - 2)) 
                inY = 1; 
            break;

        case LEFT:
            if(--inX < 1)  
                inX = gmRef->getBoardSizeX() - 2; 
            break;

        case RIGHT:
            if(++inX > (gmRef->getBoardSizeX() - 2)) 
                inX = 1; 
            break;

        default:
            break; 
    } 

    currHeadPos.setX(inX);  //1             
    currHeadPos.setY(inY);// TARGET      //1
    
    myPos->insertHead(currHeadPos);  // O(n) insert new head      //n

    if(!checkCollision())    //n^2 isn't reached if returns 0       // check collision.  If collision happens, then omega(n^2)
        myPos->removeTail();  //1       // removeTail.  Otherwise, generate new item.    
    
    if(killable)    //assume false                       
        if(checkSelfCollision()) //n
            gmRef->setGameLost();    //theta(1)   // If colliding with itself, end game.
     
}    

    
bool Player::checkCollision()  // private
{    
    // 1. Check Item Bin for Item ObjPos
    objPos target = binRef->getItem();  
    bool collided = myPos->getHead().isOverlap(&target);  // returns 0

    // 2. check whether objPos are equal
    if(collided) // condition never entered if collided == 0
    {
        // 3. If yes, collision takes place
        // Generate New Item(s)
        binRef->generateItem(); //n^2

        // Increase Score by Number
        myScore += target.getNum();
    }

    return collided; // return assumed false value for part H
}

bool Player::checkSelfCollision()  // private
{    
    // Make sure snake is long enough to kill itself
    int length = myPos->getSize(); 
    if(length < 4) return false;  //theta(1)

    // Then check for self collision
    myPos->resetReadPos(); 
    objPos tempPos; 
    objPos headPos = myPos->getNext();
    
    for(int i = 1; i < length; i++)  //O(n) due to if statement
    {
        tempPos = myPos->getNext();
        if(headPos.isOverlap(&tempPos))
        {
            // set game end.
            return true;
        }
    }

    return false; // if reaching this point, then theta(n) for this function
}


void Player::drawPlayer()  
{
    objPos targetPos;  
    int scanSize = myPos->getSize();  // get the list size  

    myPos->resetReadPos(); 
    for(int i = 0; i < scanSize; i++)  
    {
        targetPos = myPos->getNext();  
        boardRef[targetPos.getY()][targetPos.getX()] = targetPos.getSym();  
    }  
}  
    

void Player::undrawPlayer()  // private helper function
{
    objPos targetPos;  
    int scanSize = myPos->getSize();  // get the list size, theta(1)
 
    myPos->resetReadPos();  
    for(int i = 0; i < scanSize; i++) // theta(n)
    {
        targetPos = myPos->getNext(); 
        boardRef[targetPos.getY()][targetPos.getX()] = ' ';  
    }
}  
    


void Player::increaseScore()
{
    myScore++;
}

int Player::getScore() const
{
    return myScore;    
}

objPosList* Player::getPlayerPos() const
{
    return myPos;   
}  
    
