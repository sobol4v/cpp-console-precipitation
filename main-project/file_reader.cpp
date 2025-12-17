#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "file_reader.h"

using namespace std;

// Чтение данных из файла
int readData(const char* filename, RainRecord arr[], int maxSize) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Файл " << filename << " не найден!" << endl;
        return 0;
    }

    string line;
    int count = 0;
    while (getline(fin, line) && count < maxSize) {
        istringstream iss(line);
        iss >> arr[count].day >> arr[count].month >> arr[count].amount;
        getline(iss, arr[count].type);
        if (!arr[count].type.empty() && arr[count].type[0] == ' ')
            arr[count].type.erase(0, 1);
        count++;
    }
    fin.close();
    return count;
}

// Вывод записи
void printRecord(const RainRecord& r) {
    cout << r.day << "." << r.month << " " << r.amount << " " << r.type << endl;
}

// Сравнения для сортировки
bool cmpAmount(RainRecord* a, RainRecord* b) {
    return a->amount < b->amount;
}

bool cmpTypeMonthDay(RainRecord* a, RainRecord* b) {
    if (a->type != b->type) return a->type < b->type;
    if (a->month != b->month) return a->month < b->month;
    return a->day < b->day;
}

// Шейкерная сортировка
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

// Быстрая сортировка
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
