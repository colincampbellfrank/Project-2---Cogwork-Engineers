//
// Created by colin on 11/2/2026.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "DataPoint.h"


using namespace std;

int main() {
    ifstream file("WHO-COVID-19-global-daily-data.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;

    //skip header
    getline(file, line);

    //allocate vector so process of loading everything is faster
    vector<DataPoint> data;
    data.reserve(583441);

    //read line by line, skipping country_code since redundant for us
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> row;

        while (getline(ss, field, ',')) {
            row.push_back(field);
        }

        DataPoint data_point=DataPoint(row[0], row[2], row[3], row[4], row[5], row[6], row[7]);
        data.push_back(data_point);
    }
    file.close();

    return 0;
}
}