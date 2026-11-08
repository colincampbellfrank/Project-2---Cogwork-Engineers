#include "FeatureLog.h"

using namespace std;

FeatureLog::FeatureLog() {}

void FeatureLog::logRanking(const string& date, const string& metric, int topK, long long heapTimeUs, long long treeTimeUs, const string& summary) {
    LogEntry entry;
    entry.queryNum = (int)entries.size() + 1;
    entry.featureName = "Country Ranking";
    entry.parameters = "Date: " + date + ", Metric: " + metric + ", Top: " + to_string(topK);
    entry.heapTimeUs = heapTimeUs;
    entry.treeTimeUs = treeTimeUs;
    entry.summary = summary;
    entries.push_back(entry);
}

void FeatureLog::logGrowthRate(const string& country, const string& startDate, const string& endDate, double growthRate, long long timeUs) {
    LogEntry entry;
    entry.queryNum = (int)entries.size() + 1;
    entry.featureName = "Growth Rate";
    entry.parameters = "Country: " + country + ", Range: " + startDate + " to " + endDate;
    entry.heapTimeUs = timeUs;
    entry.treeTimeUs = -1;
    entry.summary = "Growth: " + to_string((int)growthRate) + "%";
    entries.push_back(entry);
}

void FeatureLog::displayLog() const {
    cout << "\n--- Feature Access History Log ---\n";
    if (entries.empty()) {
        cout << "[No features accessed yet in this session.]\n";
        return;
    }

    cout << left << setw(6) << "Query" << setw(18) << "Feature" << setw(12) << "Heap (us)" << setw(12) << "Tree (us)" << "Parameters | Summary\n";

    for (const auto& entry : entries) {
        string treeStr = (entry.treeTimeUs >= 0) ? to_string(entry.treeTimeUs) : "N/A";
        cout << left << setw(6) << ("#" + to_string(entry.queryNum))
             << setw(18) << entry.featureName
             << setw(12) << entry.heapTimeUs
             << setw(12) << treeStr
             << entry.parameters << " | " << entry.summary << "\n";
    }
}

void FeatureLog::clear() {
    entries.clear();
    cout << "Feature access log cleared.\n";
}

int FeatureLog::getCount() const {
    return (int)entries.size();
}
