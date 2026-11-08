#include "MenuUI.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std;

MenuUI::MenuUI(vector<DataPoint>& data, BPlusTree& tree) : dataset(data), bPlusTree(tree) {}

int MenuUI::getAttributeValue(DataPoint& dp, const string& attribute) {
    if (attribute == "new_cases")
        return dp.getNewCases();
    if (attribute == "tot_cases")
        return dp.getTotCases();
    if (attribute == "new_deaths")
        return dp.getNewDeaths();
    if (attribute == "tot_deaths")
        return dp.getTotDeaths();
    return 0;
}

string MenuUI::getMetricDisplayName(const string& attr) {
    if (attr == "new_cases")
        return "New Cases";
    if (attr == "tot_cases")
        return "Total Cases";
    if (attr == "new_deaths")
        return "New Deaths";
    if (attr == "tot_deaths")
        return "Total Deaths";
    return attr;
}

bool MenuUI::isValidDate(const string& dateStr) {
    if (dateStr.length() != 10)
        return false;
    if (dateStr[4] != '-' || dateStr[7] != '-')
        return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(dateStr[i]))
            return false;
    }
    return true;
}

void MenuUI::handleRankCountries() {
    cout << "\n--- Rank Countries by Characteristic ---\n";

    string date;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    if (!isValidDate(date)) {
        cout << "Invalid date format. Expected YYYY-MM-DD.\n";
        return;
    }

    cout << "Select Metric:\n";
    cout << "1. New Cases\n";
    cout << "2. Cumulative Total Cases\n";
    cout << "3. New Deaths\n";
    cout << "4. Cumulative Total Deaths\n";
    cout << "Choice (1-4): ";

    int metricChoice;
    if (!(cin >> metricChoice) || metricChoice < 1 || metricChoice > 4) {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Invalid choice.\n";
        return;
    }

    string metric;
    if (metricChoice == 1)
        metric = "new_cases";
    else if (metricChoice == 2)
        metric = "tot_cases";
    else if (metricChoice == 3)
        metric = "new_deaths";
    else
        metric = "tot_deaths";

    int topK = 10;
    cout << "Enter number of top countries to display (e.g. 10): ";
    if (!(cin >> topK) || topK <= 0) {
        topK = 10;
        cin.clear();
    }

    auto heapStart = chrono::high_resolution_clock::now();
    vector<DataPoint> datePoints;
    for (auto& dp : dataset)
        if (dp.getDate() == date)
            datePoints.push_back(dp);

    DataHeap heap(metric);
    for (const auto& dp : datePoints)
        heap.insert(dp);

    vector<DataPoint> heapResults;
    int kHeap = min(topK, heap.getSize());
    for (int i = 0; i < kHeap; ++i)
        heapResults.push_back(heap.pop());

    auto heapEnd = chrono::high_resolution_clock::now();
    long long heapTimeUs = chrono::duration_cast<chrono::microseconds>(heapEnd - heapStart).count();

    auto treeStart = chrono::high_resolution_clock::now();
    vector<DataPoint> treePoints = bPlusTree.searchByDate(date);

    sort(treePoints.begin(), treePoints.end(), [this, &metric](DataPoint& a, DataPoint& b) {
        return getAttributeValue(a, metric) > getAttributeValue(b, metric);
    });

    vector<DataPoint> treeResults;
    int kTree = min((size_t)topK, treePoints.size());
    for (int i = 0; i < kTree; ++i)
        treeResults.push_back(treePoints[i]);

    auto treeEnd = chrono::high_resolution_clock::now();
    long long treeTimeUs = chrono::duration_cast<chrono::microseconds>(treeEnd - treeStart).count();

    if (heapResults.empty()) {
        cout << "No records found for date: " << date << "\n";
        return;
    }

    cout << "\nRankings on " << date << " by " << getMetricDisplayName(metric) << " (Top " << heapResults.size() << "):\n";
    cout << left << setw(6) << "Rank" << setw(32) << "Country" << setw(16) << "Region" << right << setw(15) << getMetricDisplayName(metric) << "\n";

    for (size_t i = 0; i < heapResults.size(); ++i) {
        int val = getAttributeValue(heapResults[i], metric);
        cout << left << setw(6) << (i + 1) << setw(32) << heapResults[i].getCountry() << setw(16) << heapResults[i].getRegion() << right << setw(15) << val << "\n";
    }

    cout << "\nMax-Heap time: " << heapTimeUs << " us (" << (heapTimeUs / 1000.0) << " ms)\n";
    cout << "B+ Tree time:  " << treeTimeUs << " us (" << (treeTimeUs / 1000.0) << " ms)\n";

    string summary = "#1: " + heapResults[0].getCountry() + " (" + to_string(getAttributeValue(heapResults[0], metric)) + ")";
    featureLog.logRanking(date, metric, topK, heapTimeUs, treeTimeUs, summary);
}

void MenuUI::handleGrowthRate() {
    cout << "\n--- Country Growth Rate Evaluation ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string country;
    cout << "Enter country name: ";
    getline(cin, country);

    string startDate, endDate;
    cout << "Enter start date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter end date (YYYY-MM-DD): ";
    cin >> endDate;

    if (!isValidDate(startDate) || !isValidDate(endDate)) {
        cout << "Invalid date format. Expected YYYY-MM-DD.\n";
        return;
    }

    auto startClock = chrono::high_resolution_clock::now();
    DataPoint* startPoint = nullptr;
    DataPoint* endPoint = nullptr;

    for (auto& dp : dataset) {
        if (dp.getCountry() == country) {
            if (dp.getDate() == startDate)
                startPoint = &dp;
            if (dp.getDate() == endDate)
                endPoint = &dp;
        }
        if (startPoint && endPoint)
            break;
    }

    auto endClock = chrono::high_resolution_clock::now();
    long long elapsedUs = chrono::duration_cast<chrono::microseconds>(endClock - startClock).count();

    if (!startPoint || !endPoint) {
        cout << "Error: Could not find records for " << country << " on both dates.\n";
        return;
    }

    int casesStart = startPoint->getTotCases();
    int casesEnd = endPoint->getTotCases();
    int deathsStart = startPoint->getTotDeaths();
    int deathsEnd = endPoint->getTotDeaths();

    int casesDiff = casesEnd - casesStart;
    int deathsDiff = deathsEnd - deathsStart;

    double caseGrowthPct = (casesStart > 0) ? ((double)casesDiff / casesStart * 100.0) : 0.0;
    double deathGrowthPct = (deathsStart > 0) ? ((double)deathsDiff / deathsStart * 100.0) : 0.0;

    cout << "\nGrowth Rate for " << country << " (" << startDate << " to " << endDate << "):\n";
    cout << left << setw(20) << "Metric" << setw(15) << startDate << setw(15) << endDate << setw(15) << "Net Change" << "Growth (%)\n";
    cout << left << setw(20) << "Total Cases" << setw(15) << casesStart << setw(15) << casesEnd << setw(15) << casesDiff << fixed << setprecision(2) << caseGrowthPct << "%\n";
    cout << left << setw(20) << "Total Deaths" << setw(15) << deathsStart << setw(15) << deathsEnd << setw(15) << deathsDiff << fixed << setprecision(2) << deathGrowthPct << "%\n";
    cout << "Lookup time: " << elapsedUs << " us (" << (elapsedUs / 1000.0) << " ms)\n";

    featureLog.logGrowthRate(country, startDate, endDate, caseGrowthPct, elapsedUs);
}

void MenuUI::handleDisplayLog() {
    featureLog.displayLog();
}

void MenuUI::handleDatasetSummary() {
    cout << "\nDataset Summary:\n";
    cout << "Total records loaded: " << dataset.size() << "\n";
    if (!dataset.empty()) {
        cout << "Start date: " << dataset.front().getDate() << " (" << dataset.front().getCountry() << ")\n";
        cout << "End date:   " << dataset.back().getDate() << " (" << dataset.back().getCountry() << ")\n";
    }
    cout << "Queries logged: " << featureLog.getCount() << "\n";
}

void MenuUI::run() {
    while (true) {
        cout << "\nMenu Options:\n";
        cout << "1. Rank countries by characteristic for a date\n";
        cout << "2. Evaluate country growth rate between two dates\n";
        cout << "3. View feature access log\n";
        cout << "4. View dataset summary\n";
        cout << "5. Clear feature log\n";
        cout << "6. Exit\n";
        cout << "Enter choice (1-6): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            string discard;
            getline(cin, discard);
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleRankCountries();
                break;
            case 2:
                handleGrowthRate();
                break;
            case 3:
                handleDisplayLog();
                break;
            case 4:
                handleDatasetSummary();
                break;
            case 5:
                featureLog.clear();
                break;
            case 6:
                cout << "Exiting. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                break;
        }
    }
}
