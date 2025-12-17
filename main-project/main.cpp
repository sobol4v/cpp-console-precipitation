#include <iostream>
#include <vector>
#include "precipitation.h"
#include "file_reader.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    RainRecord records[MAX_RECORDS];
    int size = readData("data.txt", records, MAX_RECORDS);

    cout << "Все данные:\n";
    for (int i = 0; i < size; i++) printRecord(records[i]);

    cout << "\nДни с дождем:\n";
    for (int i = 0; i < size; i++)
        if (records[i].type.find("дождь") != string::npos) printRecord(records[i]);

    cout << "\nДни с осадками < 1.5:\n";
    for (int i = 0; i < size; i++)
        if (records[i].amount < 1.5) printRecord(records[i]);

    // Создаём массив указателей для сортировки
    vector<RainRecord*> ptrs;
    for (int i = 0; i < size; i++) ptrs.push_back(&records[i]);

    int choiceSort, choiceCrit;
    cout << "\nВыберите метод сортировки:\n1 - Шейкерная\n2 - Быстрая\n> ";
    cin >> choiceSort;
    cout << "Выберите критерий сортировки:\n1 - по количеству осадков\n2 - по характеристике/месяцу/дню\n> ";
    cin >> choiceCrit;

    bool (*cmpFunc)(RainRecord*, RainRecord*) = (choiceCrit == 1) ? cmpAmount : cmpTypeMonthDay;

    if (choiceSort == 1) shakerSort(ptrs, cmpFunc);
    else quickSort(ptrs, 0, ptrs.size() - 1, cmpFunc);

    cout << "\nОтсортированные данные:\n";
    for (auto r : ptrs) printRecord(*r);

    return 0;
}
