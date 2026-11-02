#ifndef PROJECT_TWO_BPLUS_H
#define PROJECT_TWO_BPLUS_H

#include <utility>
#include <vector>
#include "DataPoint.h"

class BST
{
    struct TreeNode
    {
        bool isLeaf;
        TreeNode* next;

        std::vector<DataPoint> data;
        std::vector<TreeNode*> children;

        explicit TreeNode() : data({}), children({}){};
    };


public:

};

#endif //PROJECT_TWO_BPLUS_H'