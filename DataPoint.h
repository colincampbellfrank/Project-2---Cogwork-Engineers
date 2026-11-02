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
    DataPoint(string _date, string _country, string _region, string _new_cases, string _tot_cases, string _new_deaths, string _tot_deaths) : date(_date), country(_country), region(_region), new_cases(_new_cases), tot_cases(_tot_cases), new_deaths(_new_deaths), tot_deaths(_tot_deaths) {}
public:
    //Get functions for the private attributes
    void getDate() {
        return date;
    }
    void getCountry() {
        return country;
    }
    void getRegion() {
        return region;
    }
    void getNewCases() {
        return new_cases;
    }
    void getTotCases() {
        return tot_cases;
    }
    void getNewDeaths() {
        return new_deaths;
    }
    void getTotDeaths() {
        return tot_deaths;
    }
};


#endif //PROJECT_2_COGWORK_ENGINEERS_DATAPOINT_H