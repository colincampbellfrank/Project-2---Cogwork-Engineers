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
        // Note to self, if key_count is not used, remove it
        int key_count = 0;

        std::vector<DataPoint> keys;
        std::vector<TreeNode*> children;

        // empty node constructor
        TreeNode(bool _is_leaf) : is_leaf(_is_leaf), key_count(0), keys({}), children({}) {};

        // node constructor with data point
        TreeNode(DataPoint _data, bool _is_leaf) : is_leaf(_is_leaf), key_count(1), keys({ _data}), children({}) {};
    };

    TreeNode* root = nullptr;
    std::string focus_attribute;
    int max_keys;

    // helper functions (insert)
    void split(TreeNode* parent, TreeNode* child, int index);
    void insert_non_full(TreeNode* node, DataPoint data_point);

    int getFocusAttribute(DataPoint& dp);

public:

    // ----------- BPlusTree Constructors Here ------------

    // Creates an empty B+ Tree sorted by the specified attribute
    //  Attribute options: (tot = total)
        // "date", "new_cases", "tot_cases", "new_deaths", "tot_deaths"
    // Will default to "date" if an invalid attribute is specified

    // Use the first constructor for a tree with many nodes, such as if all of the data points are being inserted into the tree (240 allows for each country to have a data point stored in a date)
    // Use the second for customization of the maximum number of keys per node in the B+ Tree in case of smaller trees
    BPlusTree(std::string attribute) : focus_attribute(attribute), max_keys(240) {
        if (attribute != "new_cases" && attribute != "tot_cases" && attribute != "new_deaths" && attribute != "tot_deaths") {
            focus_attribute = "date";
        }
    }

    BPlusTree(std::string attribute, int _max_keys) : focus_attribute(attribute), max_keys(_max_keys) {
        if (attribute != "new_cases" && attribute != "tot_cases" && attribute != "new_deaths" && attribute != "tot_deaths") {
            focus_attribute = "date";
        }
    }



    // ------------ BPlusTree Functions Here ------------


    // Inserts a DataPoint into the B+ Tree
            // Notes:
            // If the specified attribute is tied (ex: total_deaths = total_deaths), the insertion will resort
            // to using the date to break the tie and then country alphabetically if the date is also tied
    void insert(DataPoint &dataPoint);



    // -------- Searches --------

    // Use these searches when the focus attribute is NOT 'date'
    // The first one will return all data points with the specified attribute value, 
    // the second will return only data points for the specified country
    std::vector<DataPoint> searchByAttribute(int attribute_value);
    std::vector<DataPoint> searchByAttribute(int attribute_val, std::string country);


    // Use these searches when the focus attribute IS 'date'
    // The first one will return all data points with the specified date,
    // the second will return only data points for the specified country
    std::vector<DataPoint> searchByDate(std::string date);
    std::vector<DataPoint> searchByDate(std::string date, std::string country);

};

#endif //PROJECT_TWO_BPLUS_H'
