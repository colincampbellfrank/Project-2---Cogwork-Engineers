#include "bPlus.h"
#include <utility>
#include <iostream>
#include <ostream>



// ----------- Tree Functions Here ------------


int BPlusTree::insert(DataPoint data_point)
{
    
    // If tree is empty, create a new root node and insert the data point
    if (root == nullptr) {
        root = new TreeNode(data_point, true);
        return 1;
    }

    return 0;
}

// Internal function for splitting nodes when exceeding maximum keys.
void BPlusTree::split(TreeNode * parent, TreeNode * child, int index)
{
    // Gets a readable variable for the median index and value
    int median_index = child->key_count / 2;
    DataPoint median = child->keys[median_index];
    // Creates a new node based on whether the spliting node is a leaf or not
    TreeNode* new_node = new TreeNode(child->is_leaf);

    // Inserts the new node (child) and median (key) into the parent node
    parent->children.insert(parent->children.begin() + index + 1, new_node);
    parent->keys.insert(parent->keys.begin() + index, median);

    // If the child is NOT a leaf, we need to move the keys and children to the new node. 
        // Note:
        // +1 is used when not a leaf as the median node is moved up and removed from the child node

    if (!child->is_leaf) {
        // Moves upper half of keys (except the median) to the new node
        new_node->keys.assign(child->keys.begin() + median_index + 1, child->keys.end());
        child->keys.resize(median_index);
        
        // moves upper half of children to the new node
        new_node->children.assign(child->children.begin() + median_index + 1, child->children.end());
        child->children.resize(median_index + 1);
    
    
    // If it IS a leaf, we only need to move the keys and update the next pointer.
    } else {
        // moves upper half of keys to the new node
        new_node->keys.assign(child->keys.begin() + median_index, child->keys.end());
        child->keys.resize(median_index);

        // Ensures the new leaf is properly connected to the next leaf, and the old one to it
        new_node->next = child->next;
        child->next = new_node;
    }

    // Updates the key counts for all involved nodes
    parent->key_count = parent->keys.size();
    new_node->key_count = new_node->keys.size();
    child->key_count = child->keys.size();
}