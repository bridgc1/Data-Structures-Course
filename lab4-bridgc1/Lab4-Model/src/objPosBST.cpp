#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    root = NULL;
    // Constructor (Check Lecture Notes for Implementation, Simple)
}

objPosBST::~objPosBST()
{
    // Destructor
    deleteTree();
    root = NULL;
    // Invoke delete tree, then set root to NULL
}

void objPosBST::deleteTree(const TNode* thisNode)
{
    if (thisNode == NULL) return;
    
    deleteTree(thisNode->right);
    deleteTree(thisNode->left);
    delete thisNode;    
    
	// Delete all nodes in the tree
    
    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    if (root == NULL)
        return true;

    return false;
    // Check if tree is empty
    //  Really simple, think about how.
}


bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos
    if (thisNode == NULL)
        return false;
    if (thisPos.getPF() == thisNode->data.getPF())
        if (thisNode->right == nullptr && thisNode->left == nullptr)
            return true;
        else
            return false;
    else{
        if (thisPos.getPF() > thisNode->data.getPF()) //if current prefix is larger than node's prefix, go to right sibling
            return isLeaf(thisPos, thisNode->right);
        else //if current prefix is smaller than node's prefix, go to left sibling
            return isLeaf(thisPos, thisNode->left);
    }
    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node

    // Remember, leaf nodes do not have children nodes
}

bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root);
}


void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    if (thisNode != NULL)
    {
        printTree(thisNode->left);
        cout << thisNode->data.getPF() << thisNode->data.getNum() << ' ';
        printTree(thisNode->right);
    }

    
    // Print the entire tree content using **In-Order Traversal**

    // print in the format of Prefix + Number
    // e.g.  N30 P25 etc.

    // DO NOT use printObjPos() as it will mess up the game display.
}

void objPosBST::printTree() const  // public interface
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);
}


int objPosBST::getHeight(const TNode* thisNode) const
{
    if (thisNode == NULL)
        return 0;
    
    // Tree Height Calculation Algorithm 

    int height_right = getHeight(thisNode->right);

        int height_left = getHeight(thisNode->left);
    
    if (height_left > height_right)
        return height_left+1;
    else if (height_left <= height_right)
        return height_right+1;

    // 1. If thisNode is null, height is zero.

    // 2. Otherwise, recursively invoke getHeight for the left and right subtree, and save
    //    the returned heights.

    // 3. Compare the two returned heights, and return the larger one.
}

void objPosBST::printCurrentLevel(const TNode* thisNode, const int level) const
{

    if (thisNode != NULL)
    {
        int height = getHeight(root); 
        if (thisNode->right == NULL && thisNode->left == NULL) //if at leaf node, don't print anything
            return;
        if (level == 1)
        {
           
            cout << " ";
            cout  << thisNode->data.getPF() << " ";
            
        }
        
        else{
               
                printCurrentLevel(thisNode->left, level-1);
                if (thisNode->left == NULL || thisNode->right == NULL)
                    cout << " ";
                cout << " ";
                printCurrentLevel(thisNode->right, level-1);
            }
    }
    
    
    // Recursive Level-Order Tree-Printing Algorithm 
    
  
    // 1. First check if at leaf node.  If yes, do not print anything

    // 2. Then, check if level is 1.  If yes, print the Prefix field only (specified in manual)

    // 3. Otherwise, invoke recursively printCurrentLevel for left subtree with one less level, then
    //                                                        right subtree with one less level
    //    "if I'm not at the level, keep on searching into the left and the right subtrees"

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

// Public Interface.
void objPosBST::printTreeLevel() const
{
    if (root == NULL)
        return;

    int height = getHeight(root);
    
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= height - i; j++)
        {
            cout << " ";
        }
        printCurrentLevel(root, i);  
        cout << endl;
    }

    
    // Interface to the Recursive Version of Level-Order Tree-Printing Algorithm 

    // 1. Get the height of the tree
    // 2. For each level (bounded by height), invoke the recursive tree-printing algorithm.

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos
    if (thisNode == NULL)
        return false; //if current node is null
    if (thisPos.getPF() > thisNode->data.getPF())
    {
        isInTree(thisPos, thisNode->right);
    }
    else if (thisPos.getPF() < thisNode->data.getPF())
    {
        isInTree(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() == thisNode->data.getPF())
    {
        return true;
    }
    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, return true
}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    if (thisNode == NULL)
    {
        thisNode = new TNode(thisPos);
        return;
    }
    if (thisPos.getPF() > thisNode->data.getPF())
    {
        insert(thisPos, thisNode->right);
    }
    else if (thisPos.getPF() < thisNode->data.getPF())
    {
        insert(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() == thisNode->data.getPF())
    {
        thisNode->data.setNum(thisNode->data.getNum() + thisPos.getNum()); //sum the current node's number and the number from thisPos
    }
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification: 

    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)
}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}


const TNode* objPosBST::findMin(const TNode* thisNode) const
{
    if (thisNode != NULL)
    {
        while (thisNode->left != NULL)
        {
            thisNode = thisNode->left;
        }
        return thisNode;
    }
    
	// Find the node with the smallest prefix in the subtree from thisNode

    // Used as part of remove() algorithm

    // Check Lecture Notes for implementation
}


void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
    if (thisNode == NULL)
        return;
    if (thisPos.getPF() < thisNode->data.getPF())
        remove(thisPos, thisNode->left);
    else if (thisPos.getPF() > thisNode->data.getPF())
        remove (thisPos, thisNode->right);
    else{
    // else the prefixes are equal:
    // for removal need to account for 3 cases: leaf node, parent to two children, parent to one child
        if (thisNode->right == NULL && thisNode->left == NULL) //case 1: leaf
        {
            delete thisNode;
            thisNode = NULL;
        }
        else if (thisNode->right != NULL && thisNode->left != NULL) //case 2: parent of two children
        {
            thisNode->data = findMin(thisNode->right)->data; //replaced the removed node with the minimum value on the right side of this node
            remove(thisNode->data, thisNode->right); //now find the minimum node that contains the data from the node used to replace the removed node and remove it
        }
        else //case 3: parent to one child
        {
            TNode* oldNode = thisNode; //create temporary node so can delete curent node later
            thisNode = (thisNode->left != NULL) ? thisNode->left : thisNode->right;
            //thisNode and thisPos data are equal, however if thisNode has a left child then redirect pointer to that child, else point to the right child
            delete oldNode;
            oldNode = NULL;
        }
    }
    
   
        
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)
}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold
    if (thisNode == NULL) return false;
    if (thisNode->data.getNum() > numThreshold)
    {
        return true;
    }
    else
    {
        return findGreater(numThreshold, thisNode->left) || findGreater(numThreshold, thisNode->right);
    }
   

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.
}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}