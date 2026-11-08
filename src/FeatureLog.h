#ifndef PROJECT_2_COGWORK_ENGINEERS_FEATURELOG_H
#define PROJECT_2_COGWORK_ENGINEERS_FEATURELOG_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct LogEntry {
    int queryNum;
    string featureName;
    string parameters;
    long long heapTimeUs;
    long long treeTimeUs;
    string summary;
};

class FeatureLog {
private:
    vector<LogEntry> entries;

public:
    FeatureLog();
    void logRanking(const string& date, const string& metric, int topK, long long heapTimeUs, long long treeTimeUs, const string& summary);
    void logGrowthRate(const string& country, const string& startDate, const string& endDate, double growthRate, long long timeUs);
    void displayLog() const;
    void clear();
    int getCount() const;
};

#endif //PROJECT_2_COGWORK_ENGINEERS_FEATURELOG_H
