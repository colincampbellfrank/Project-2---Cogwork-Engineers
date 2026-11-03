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
    int capacity;
    const string attribute; //identify what kind of max heap we are making based on the input
public:
    DataHeap(int _capacity, const string &_attribute) : capacity(_capacity), attribute(_attribute) {
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
    //buildHeap function unnecessary

};




#endif //PROJECT_2___COGWORK_ENGINEERS_DATAHEAP_H