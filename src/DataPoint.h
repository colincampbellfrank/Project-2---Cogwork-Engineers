//
// Created by colin on 11/2/2026.
//

#ifndef PROJECT_2_COGWORK_ENGINEERS_DATAPOINT_H
#define PROJECT_2_COGWORK_ENGINEERS_DATAPOINT_H

#include <string>

using namespace std;

class DataPoint {
private:
    string date;
    string country;
    string region;
    int new_cases;
    int tot_cases;
    int new_deaths;
    int tot_deaths;

    static int parseSafe(const string& s) {
        if (s.empty())
            return 0;
        return stoi(s);
    }

public:
    DataPoint() : date(""), country(""), region(""), new_cases(0), tot_cases(0), new_deaths(0), tot_deaths(0) {}
    DataPoint(string _date, string _country, string _region, string _new_cases, string _tot_cases, string _new_deaths, string _tot_deaths) : date(_date), country(_country), region(_region), new_cases(parseSafe(_new_cases)), tot_cases(parseSafe(_tot_cases)), new_deaths(parseSafe(_new_deaths)), tot_deaths(parseSafe(_tot_deaths)) {}

    //Get functions for the private attributes
    string getDate() {
        return date;
    }
    string getCountry() {
        return country;
    }
    string getRegion() {
        return region;
    }
    int getNewCases() {
        return new_cases;
    }
    int getTotCases() {
        return tot_cases;
    }
    int getNewDeaths() {
        return new_deaths;
    }
    int getTotDeaths() {
        return tot_deaths;
    }
};

#endif //PROJECT_2_COGWORK_ENGINEERS_DATAPOINT_H
