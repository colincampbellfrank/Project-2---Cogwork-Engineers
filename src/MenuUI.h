#ifndef PROJECT_2_COGWORK_ENGINEERS_MENUUI_H
#define PROJECT_2_COGWORK_ENGINEERS_MENUUI_H

#include <vector>
#include <string>
#include "DataPoint.h"
#include "DataHeap.h"
#include "bPlus.h"
#include "FeatureLog.h"

using namespace std;

class MenuUI {
private:
    vector<DataPoint>& dataset;
    BPlusTree& bPlusTree;
    FeatureLog featureLog;

    // Helper functions
    void handleRankCountries();
    void handleGrowthRate();
    void handleDisplayLog();
    void handleDatasetSummary();

    int getAttributeValue(DataPoint& dp, const string& attribute);
    string getMetricDisplayName(const string& attr);
    bool isValidDate(const string& dateStr);

public:
    MenuUI(vector<DataPoint>& data, BPlusTree& tree);

    void run();
};

#endif //PROJECT_2_COGWORK_ENGINEERS_MENUUI_H
