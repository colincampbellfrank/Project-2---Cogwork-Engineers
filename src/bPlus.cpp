#include "bPlus.h"
#include <utility>
#include <iostream>
#include <ostream>



// ----------- Tree Functions Here ------------


int BPlusTree::insert(DataPoint data_point)
{
    
    // If tree is empty, create a new root node and insert the data point
    if (root == nullptr) {
        root = new TreeNode(data_point);
        return 1;
    }

    return 0;
}

// Internal function for splitting nodes when exceeding maximum keys.
int BPlusTree::split(TreeNode * parent, TreeNode * child, int index)
{
return 0;
}