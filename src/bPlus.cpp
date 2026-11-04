#include "bPlus.h"
#include <utility>
#include <iostream>
#include <ostream>
#include <functional>


// ----------- Tree Function Definitions Here ------------
// Check bPlus.h for function descriptions and use instructions

void BPlusTree::insert(DataPoint data_point)
{
    
    // If tree is empty, create a new root node and insert the data point
    if (root == nullptr) {
        root = new TreeNode(data_point, true);
    }

    else {
        
        // If the root node is full, first split it and create a new root node
        if (root->key_count == max_keys) {
            TreeNode* new_root = new TreeNode(false);
            new_root->children.push_back(root);
            split(new_root, root, 0);
            root = new_root;
        }

        // Insert the data point into the appropriate node
        insert_non_full(root, data_point);

    }
}


// Internal function for inserting a data point into a specified node
void BPlusTree::insert_non_full(TreeNode * node, DataPoint data_point)
{
    std::string date = data_point.getDate();
    std::string country = data_point.getCountry();

    // create a function to get all focus attribute values so checking between them is not required late (except for date)
    std::function<int(DataPoint&)> get_focus_value;
    if (focus_attribute == "new_cases") {
        get_focus_value = [](DataPoint& dp) { return dp.getNewCases(); };
    } else if (focus_attribute == "tot_cases") {
        get_focus_value = [](DataPoint& dp) { return dp.getTotCases(); };
    } else if (focus_attribute == "new_deaths") {
        get_focus_value = [](DataPoint& dp) { return dp.getNewDeaths(); };
    } else if (focus_attribute == "tot_deaths") {
        get_focus_value = [](DataPoint& dp) { return dp.getTotDeaths(); };
    }

    if (node->is_leaf){

        node->keys.insert(upper_bound(node->keys.begin(), node->keys.end(), data_point, 
            //as DataPoint is a custom class, a lambda function is used for comparison of the focus attribute
            [this, get_focus_value](DataPoint& a, DataPoint& b) {

                // checks every possible focus attribute for if they are tied, and if not, returns the comparison
                if (focus_attribute != "date") {
                    if (get_focus_value(a) != get_focus_value(b)) {
                        return get_focus_value(a) < get_focus_value(b);
                    }
                
                // in the case of a tie, or the focus attribute is 'date', compare by date, and then country if the date is also tied
                } else {
                    if (a.getDate() != b.getDate()) {
                        return a.getDate() < b.getDate();
                    } else {
                        return a.getCountry() < b.getCountry();
                    }
                }

            }
        ), data_point ); 
    }

    // in the case where the node is not a leaf
    else {
        // Find the index(i) of the child node to insert into, based on the focus attribute and date/country for tie-breaking
        int i = node->keys.size() - 1;
        while (i >= 0 && get_focus_value(data_point) < get_focus_value(node->keys[i]) && data_point.getDate() < node->keys[i].getDate() && data_point.getCountry() < node->keys[i].getCountry()) {
            i--;
        }
        i++;

        if (node->children[i]->key_count == max_keys) {
            split(node, node->children[i], i);
            // if the new data point is greater than the median, we need to insert into the new child node
            // the three different cases are for the different level of tie-breaking (focus attribute, date, country)
            if (get_focus_value(data_point) > get_focus_value(node->keys[i]) || 
                (get_focus_value(data_point) == get_focus_value(node->keys[i]) && data_point.getDate() > node->keys[i].getDate()) || 
                (get_focus_value(data_point) == get_focus_value(node->keys[i]) && data_point.getDate() == node->keys[i].getDate() && data_point.getCountry() > node->keys[i].getCountry())) {
                i++;
            }
        }

        //insert into child node (which is guaranteed to be non-full at this point)
        insert_non_full(node->children[i], data_point);
    }
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
