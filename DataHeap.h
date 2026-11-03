//
// Created by colin on 11/3/2026.
//

#ifndef PROJECT_2___COGWORK_ENGINEERS_DATAHEAP_H
#define PROJECT_2___COGWORK_ENGINEERS_DATAHEAP_H

#include <iostream>
#include <vector>
#include <climits>
#include <string>

#include "DataPoint.h"

using namespace std;

//Geeks for Geeks max heap as reference https://www.geeksforgeeks.org/cpp/max-heap-in-cpp/
//DataHeap is a custom max heap and is changed significantly from the reference
class DataHeap {
private:
    vector<DataPoint> array;
    int size;
    const string attribute; //identify what kind of max heap we are making based on the input
    //capacity not needed
public:
    DataHeap(const string &_attribute) : attribute(_attribute) {
        size=0;
    }
    int ind_interpretAtt(int i) { //interpret one i based on attribute
        int result;
        if (attribute=="new_cases") { //check which attribute was defined
            result=array[i].getNewCases();
        }
        else if (attribute=="tot_cases") {
            result=array[i].getTotCases();
        }
        else if (attribute=="new_deaths") {
            result=array[i].getNewDeaths();
        }
        else if (attribute=="tot_deaths") {
            result=array[i].getTotDeaths();
        }
        else {
            cout<<"attribute heapify error"<<endl;
            return result;
        }
    }
    vector<int> heapify_interpretAtt(int i) { //used for heapify specifically
        vector<int> result;

        int largest=i;
        int left=2*i+1;
        int right=2*i+2;

        int left_value;
        int right_value;
        int largest_value;
        if (attribute=="new_cases") { //check which attribute was defined
            left_value=array[left].getNewCases();
            right_value=array[right].getNewCases();
            largest_value=array[largest].getNewCases();
        }
        else if (attribute=="tot_cases") {
            left_value=array[left].getTotCases();
            right_value=array[right].getTotCases();
            largest_value=array[largest].getTotCases();
        }
        else if (attribute=="new_deaths") {
            left_value=array[left].getNewDeaths();
            right_value=array[right].getNewDeaths();
            largest_value=array[largest].getNewDeaths();
        }
        else if (attribute=="tot_deaths") {
            left_value=array[left].getTotDeaths();
            right_value=array[right].getTotDeaths();
            largest_value=array[largest].getTotDeaths();
        }
        else {
            cout<<"attribute heapify error"<<endl;
            return result;
        }

        result.push_back(left_value);
        result.push_back(right_value);
        result.push_back(largest_value);
    }

    void heapify(int i) {
        int largest=i;
        int left=2*i+1;
        int right=2*i+2;

        vector<int> values=heapify_interpretAtt(i);
        int left_value=values[0];
        int right_value=values[1];
        int largest_value=values[2];

        if (left<size && left_value>largest_value) {
            largest=left;
        }
        if (right<size && right_value>largest_value) {
            largest=right;
        }
        if (largest!=i) {
            swap(array[i], array[largest]);
            heapify(largest);
        }
    }
    //buildHeap function unnecessary since we won't give an array to build from
    void insert (DataPoint point) {
        size++;
        int i=size-1;
        array[i]=point;
        int point_value=ind_interpretAtt(i); //use helper to get the relevant value based on attribute
        int parent_value=ind_interpretAtt((i-1)/2);

        while (i!=0 && parent_value<point_value) {
            swap(array[i], array[(i-1)/2]);
            i=(i-1)/2;
        }
    }
    DataPoint top() { //return attribute value of the top element
        if (size <= 0) cout<<"top error, empty heap"<<endl;
        return array[0];
    }
    DataPoint pop() {
        if (size <= 0) cout<<"pop error, empty heap"<<endl;
        if (size == 1) {
            size--;
            return array[0];
        }
        //store the maximum value, and remove it
        DataPoint root = array[0];
        array[0]=array[size - 1];
        size--;
        //heapify the root node after deletion
        heapify(0);
        return root;
    }
    //won't add DeleteKey now as I don't think it will be used in the functions required
};




#endif //PROJECT_2___COGWORK_ENGINEERS_DATAHEAP_H