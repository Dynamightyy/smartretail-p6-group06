#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =====================================================================
// PHẦN A - BẢN TẠM ĐỂ TỰ CHẠY THỬ.
// Khi ghép vào repo của nhóm: XÓA toàn bộ phần A này, vì DayRecord,
// Alert, evaluateDay đã do bạn khác viết (nhớ #include header/file
// tương ứng của nhóm). Tên field nếu khác thì sửa trong phần B.
// =====================================================================
struct DayRecord {
    string date;
    int visitors;
    int orders;
    long long revenue;
    long long targetRevenue;
    int stockouts;
};

struct Alert {
    int severity;  // 3 = HIGH, 2 = MEDIUM
    string type, detail, action;
};

// Bản đơn giản của evaluateDay: 3 luật theo đúng thứ tự trong đề
vector<Alert> evaluateDay(const DayRecord& d) {
    vector<Alert> alerts;
    if (d.stockouts > 3) {
        Alert a = {3, "Inventory Issue", "", "Check and restock shelves"};
        alerts.push_back(a);
    }
    if (d.visitors > 0 &&
        static_cast<double>(d.orders) / d.visitors * 100.0 < 20.0) {
        Alert a = {3, "Low Conversion", "", "Review customer engagement"};
        alerts.push_back(a);
    }
    if (static_cast<double>(d.revenue) / d.targetRevenue * 100.0 < 80.0) {
        Alert a = {2, "Sales Below Target", "", "Add staff support"};
        alerts.push_back(a);
    }
    return alerts;
}

// =====================================================================
// PHẦN B - CODE CỦA BẠN (Trend, Summary & Report)
// =====================================================================

// Trả về false nếu visitors = 0 (n/a); ghi kết quả vào tham chiếu conv
bool calcConversion(const DayRecord& d, double& conv) {
    if (d.visitors == 0) return false;
    conv = static_cast<double>(d.orders) / d.visitors * 100.0;
    return true;
}

// targetRevenue > 0 đã được đảm bảo lúc đọc CSV (dòng sai bị bỏ)
double calcTarget(const DayRecord& d) {
    return static_cast<double>(d.revenue) / d.targetRevenue * 100.0;
}

string alertLetters(const vector<Alert>& alerts) {
    if (alerts.empty()) return "-";
    string s = "";
    for (size_t i = 0; i < alerts.size(); i++) {
        if (alerts[i].severity == 3) s += 'H';
        else s += 'M';
    }
    return s;
}

bool hasHighAlert(const vector<Alert>& alerts) {
    for (size_t i = 0; i < alerts.size(); i++)
        if (alerts[i].severity == 3) return true;
    return false;
}

// ---------- Các hàm tính SUMMARY ----------
int countHighDays(const vector<vector<Alert> >& all) {
    int count = 0;
    for (size_t i = 0; i < all.size(); i++)
        if (hasHighAlert(all[i])) count++;
    return count;
}

// Trả về chỉ số ngày có conversion thấp nhất, -1 nếu mọi ngày đều n/a
int findLowestConversion(const vector<DayRecord>& days) {
    int best = -1;
    double bestConv = 0.0;
    for (size_t i = 0; i < days.size(); i++) {
        double conv = 0.0;
        if (!calcConversion(days[i], conv)) continue;  // bỏ ngày n/a
        if (best == -1 || conv < bestConv) {           // "<" chặt: bằng nhau giữ ngày đầu
            best = static_cast<int>(i);
            bestConv = conv;
        }
    }
    return best;
}

struct Streak {
    int length;
    int start;
    int end;
};

Streak findLongestStreak(const vector<vector<Alert> >& all) {
    Streak best = {0, -1, -1};
    int curLen = 0, curStart = -1;
    for (size_t i = 0; i < all.size(); i++) {
        if (!all[i].empty()) {
            if (curLen == 0) curStart = static_cast<int>(i);
            curLen++;
            if (curLen > best.length) {  // ">" chặt: bằng nhau giữ chuỗi trước
                best.length = curLen;
                best.start = curStart;
                best.end = static_cast<int>(i);
            }
        } else {
            curLen = 0;
        }
    }
    return best;
}

// ---------- In SUMMARY ----------
void printSummary(const vector<DayRecord>& days, const vector<vector<Alert> >& all) {
    cout << "\nSUMMARY\n";
    cout << "Days with HIGH alerts : " << countHighDays(all) << "/" << days.size() << "\n";

    int low = findLowestConversion(days);
    cout << "Lowest conversion     : ";
    if (low == -1) {
        cout << "n/a\n";
    } else {
        double conv = 0.0;
        calcConversion(days[low], conv);
        cout << days[low].date << " (" << conv << "%)\n";
    }

    Streak s = findLongestStreak(all);
    cout << "Longest alert streak  : ";
    if (s.length == 0) {
        cout << "0 days (-)\n";
    } else {
        cout << s.length << " days (" << days[s.start].date
             << " -> " << days[s.end].date << ")\n";
    }
}

// ---------- In TREND (gọi printSummary ở cuối) ----------
// days: các ngày của 1 cửa hàng, đã sắp theo date
void printTrend(const string& storeId, const vector<DayRecord>& days) {
    // Tính cảnh báo 1 lần cho mọi ngày
    vector<vector<Alert> > all;
    for (size_t i = 0; i < days.size(); i++)
        all.push_back(evaluateDay(days[i]));

    cout << fixed << setprecision(2);
    cout << "\nTREND - " << storeId << " (" << days.size() << " days)\n";
    cout << left << setw(12) << "Date" << right
         << setw(10) << "Conv" << setw(10) << "Target"
         << setw(10) << "Stockout" << "  Alerts\n";

    for (size_t i = 0; i < days.size(); i++) {
        cout << left << setw(12) << days[i].date << right;

        double conv = 0.0;
        if (calcConversion(days[i], conv)) cout << setw(9) << conv << "%";
        else                               cout << setw(10) << "n/a";

        cout << setw(9) << calcTarget(days[i]) << "%"
             << setw(10) << days[i].stockouts
             << "  " << alertLetters(all[i]) << "\n";
    }
    printSummary(days, all);
}

// =====================================================================
// PHẦN C - main CHỈ ĐỂ TEST. Khi ghép vào repo: XÓA (nhóm đã có main).
// =====================================================================
int main() {
    // TC01: dữ liệu sample S001, kết quả phải khớp mục 6 của đề
    vector<DayRecord> s001;
    s001.push_back({"2026-08-20", 150, 31, 82500000LL, 100000000LL, 3});
    s001.push_back({"2026-08-21", 180, 27, 71000000LL, 100000000LL, 5});
    s001.push_back({"2026-08-22", 160, 40, 108000000LL, 100000000LL, 1});
    printTrend("S001", s001);

    // TC06: có ngày visitors = 0 -> phải in n/a, không bị chọn là thấp nhất
    vector<DayRecord> s003;
    s003.push_back({"2026-08-14", 100, 30, 90000000LL, 100000000LL, 0});
    s003.push_back({"2026-08-15", 0, 0, 0LL, 100000000LL, 0});
    s003.push_back({"2026-08-16", 100, 25, 95000000LL, 100000000LL, 1});
    printTrend("S003", s003);

    return 0;
}