#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct DayRecord {
    string date;
    string store_id;
    int visitors;
    int orders;
    long long revenue;
    long long target_revenue;
    int stockouts;
};

bool isValidDate(const string& date) {
    if (date.size() != 10 ||
        date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;

        if (date[i] < '0' || date[i] > '9') {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1 || month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leapYear = (year % 400 == 0) ||
                    (year % 4 == 0 && year % 100 != 0);

    if (leapYear) {
        daysInMonth[1] = 29;
    }

    return day >= 1 && day <= daysInMonth[month - 1];
}

bool loadDailyStore(const string& path, vector<DayRecord>& records) {
    ifstream file(path);

    (void)records;

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << path << "\n";
        return false;
    }

    string line;
    if (!getline(file, line)) {
    cerr << "Error: Empty CSV file\n";
    return false;
};
    string expectedHeader =
    "date,store_id,visitors,orders,revenue,target_revenue,stockout_products";

    if (line != expectedHeader) {
        cerr << "Error: Invalid CSV header\n";
        return false;
    }

    int lineNumber = 1;

    while (getline(file, line)) {
    lineNumber++;

    int commaCount = count(line.begin(), line.end(), ',');

    if (commaCount != 6) {
        cerr << "Warning: Invalid column count at line "
         << lineNumber << "\n";
        continue;
    }

    stringstream ss(line);
    string date, store_id;

    getline(ss, date, ',');
    getline(ss, store_id, ',');
    
    if (date.empty() || store_id.empty()) {
        cerr << "Warning: Empty date or store_id at line "
         << lineNumber << "\n";
        continue;
    }

    if (!isValidDate(date)) {
        cerr << "Warning: Invalid date at line "
            << lineNumber << "\n";
        continue;
    }
    
    string visitors, orders, revenue, target_revenue, stockouts;

        getline(ss, visitors, ',');
        getline(ss, orders, ',');
        getline(ss, revenue, ',');
        getline(ss, target_revenue, ',');
        getline(ss, stockouts, ',');

        int visitorsNumber;
        stringstream visitorStream(visitors);
        char extra;

        if (!(visitorStream >> visitorsNumber)
            || visitorsNumber < 0
            || (visitorStream >> extra)) {

            cerr << "Warning: Invalid visitors at line "
                << lineNumber << "\n";
            continue;
        }

        int ordersNumber;
        stringstream orderStream(orders);
        char extraOrder;

        if (!(orderStream >> ordersNumber)
            || ordersNumber < 0
            || (orderStream >> extraOrder)) {

            cerr << "Warning: Invalid orders at line "
                << lineNumber << "\n";
            continue;
        }

        long long revenueNumber;
        stringstream revenueStream(revenue);
        char extraRevenue;

        if (!(revenueStream >> revenueNumber)
            || revenueNumber < 0
            || (revenueStream >> extraRevenue)) {

            cerr << "Warning: Invalid revenue at line "
                 << lineNumber << "\n";
            continue;
        }

        long long targetRevenueNumber;
        stringstream targetStream(target_revenue);
        char extraTarget;

        if (!(targetStream >> targetRevenueNumber)
            || targetRevenueNumber <= 0
            || (targetStream >> extraTarget)) {

            cerr << "Warning: Invalid target_revenue at line "
                 << lineNumber << "\n";
            continue;
        }

        int stockoutsNumber;
        stringstream stockoutStream(stockouts);
        char extraStockout;

        if (!(stockoutStream >> stockoutsNumber)
            || stockoutsNumber < 0
            || (stockoutStream >> extraStockout)) {

            cerr << "Warning: Invalid stockouts at line "
                << lineNumber << "\n";
            continue;
        }

        DayRecord record;

        record.date = date;
        record.store_id = store_id;
        record.visitors = visitorsNumber;
        record.orders = ordersNumber;
        record.revenue = revenueNumber;
        record.target_revenue = targetRevenueNumber;
        record.stockouts = stockoutsNumber;

        records.push_back(record);
}

    return true;
}


int main() {
    vector<DayRecord> records;

    if (!loadDailyStore("data/sample/daily_store.csv", records)) {
        return 1;
    }

    cout << "Total records: " << records.size() << "\n";
    cout << "CSV reading test completed!\n";

    return 0;
}