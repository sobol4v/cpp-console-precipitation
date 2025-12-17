#pragma once
#include "precipitation.h"
#include <vector>

int readData(const char* filename, RainRecord arr[], int maxSize);
void printRecord(const RainRecord& r);

void shakerSort(std::vector<RainRecord*>& arr, bool (*cmp)(RainRecord*, RainRecord*));
void quickSort(std::vector<RainRecord*>& arr, int low, int high, bool (*cmp)(RainRecord*, RainRecord*));

bool cmpAmount(RainRecord* a, RainRecord* b);
bool cmpTypeMonthDay(RainRecord* a, RainRecord* b);


