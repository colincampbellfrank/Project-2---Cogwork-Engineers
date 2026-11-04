#ifndef PROJECT_TWO_BPLUS_H
#define PROJECT_TWO_BPLUS_H

#include <utility>
#include <vector>
#include "DataPoint.h"



//Geeks for Geeks B Plus Tree implementation guide as reference https://www.geeksforgeeks.org/cpp/cpp-program-to-implement-b-plus-tree/

class BPlusTree
{
    struct TreeNode
    {
        bool is_leaf;
        TreeNode* next;
        int key_count = 0;

        std::vector<DataPoint> keys;
        std::vector<TreeNode*> children;

        // empty node constructor
        TreeNode(bool _is_leaf) :is_leaf(_is_leaf), keys({}), children({}) {};

        // node constructor with data point
        TreeNode(DataPoint _data, bool _is_leaf) : keys({ _data}), is_leaf(_is_leaf), children({}) {};
    };

    TreeNode* root = nullptr;
    std::string focus_attribute;
    int max_keys;

    void split(TreeNode* parent, TreeNode* child, int index);

public:

    // Creates an empty B+ Tree sorted by the specified attribute
    BPlusTree(std::string attribute) : focus_attribute(attribute), max_keys(240) {}

    // Allows for customization of the maximum number of keys per node in the B+ Tree in case of smaller trees
    BPlusTree(std::string attribute, int _max_keys) : focus_attribute(attribute), max_keys(max_keys) {}

    // Inserts a DataPoint into the B+ Tree
    // Returns 1 if the insertion was successful, 0 if the insertion failed
            // Notes:
            // If the specified attribute is tied (ex: total_deaths = total_deaths), the insertion will resort
            // to using the date to break the tie and then country alphabetically if the date is also tied
    int insert(DataPoint dataPoint);

};

#endif //PROJECT_TWO_BPLUS_H'