#include "objPosBST.h"
#include <iostream>
using namespace std;
 //constructor, destructor, print tree, is empty, max, min, greater than, insert, remove, print tree height or level, is in tree bool, isleaf, isinternalnode, 

 objPosBST::objPosBST()
 {
    root = NULL;
 }

 ~objPosBST::objPosBST()
 {
    deleteTree();
    root = NULL;
 }
 //etc