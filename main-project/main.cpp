#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;


struct RainRecord {
    int day;
    int month;
    double amount;
    string type;
};

void printRecord(const RainRecord& r) {
    cout << r.day << "." << r.month << " " << r.amount << " " << r.type << endl;
}


void shakerSort(vector<RainRecord*>& arr, bool (*cmp)(RainRecord*, RainRecord*)) {
    int left = 0;
    int right = arr.size() - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (!cmp(arr[i], arr[i + 1])) swap(arr[i], arr[i + 1]);
        }
        right--;
        for (int i = right; i > left; i--) {
            if (!cmp(arr[i - 1], arr[i])) swap(arr[i - 1], arr[i]);
        }
        left++;
    }
}


int partition(vector<RainRecord*>& arr, int low, int high, bool (*cmp)(RainRecord*, RainRecord*)) {
    RainRecord* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (cmp(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<RainRecord*>& arr, int low, int high, bool (*cmp)(RainRecord*, RainRecord*)) {
    if (low < high) {
        int pi = partition(arr, low, high, cmp);
        quickSort(arr, low, pi - 1, cmp);
        quickSort(arr, pi + 1, high, cmp);
    }
}


bool cmpAmount(RainRecord* a, RainRecord* b) {
    return a->amount < b->amount;
}


bool cmpTypeMonthDay(RainRecord* a, RainRecord* b) {
    if (a->type != b->type) return a->type < b->type;
    if (a->month != b->month) return a->month < b->month;
    return a->day < b->day;
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<RainRecord> records;
    ifstream fin("data.txt");

    if (!fin) {
        cout << "Файл data.txt не найден!" << endl;
        return 1;
    }


    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        RainRecord r;
        iss >> r.day >> r.month >> r.amount;
        getline(iss, r.type);
        if (!r.type.empty() && r.type[0] == ' ') r.type.erase(0, 1);
        records.push_back(r);
    }
    fin.close();

    cout << "Все данные:\n";
    for (const auto& r : records) printRecord(r);


    cout << "\nДни с дождем:\n";
    for (const auto& r : records) {
        if (r.type.find("дождь") != string::npos) printRecord(r);
    }


    cout << "\nДни с осадками < 1.5:\n";
    for (const auto& r : records) {
        if (r.amount < 1.5) printRecord(r);
    }


    vector<RainRecord*> ptrs;
    for (auto& r : records) ptrs.push_back(&r);


    int choiceSort, choiceCrit;
    cout << "\nВыберите метод сортировки:\n1 - Шейкерная\n2 - Быстрая\n> ";
    cin >> choiceSort;
    cout << "Выберите критерий сортировки:\n1 - по количеству осадков\n2 - по характеристике/месяцу/дню\n> ";
    cin >> choiceCrit;

    bool (*cmpFunc)(RainRecord*, RainRecord*) = (choiceCrit == 1) ? cmpAmount : cmpTypeMonthDay;

    if (choiceSort == 1) shakerSort(ptrs, cmpFunc);
    else if (choiceSort == 2) quickSort(ptrs, 0, ptrs.size() - 1, cmpFunc);


    cout << "\nОтсортированные данные:\n";
    for (auto r : ptrs) printRecord(*r);

    return 0;
}
