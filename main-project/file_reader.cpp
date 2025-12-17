#include "file_reader.h"
#include <fstream>

int readData(const char* filename, Precipitation data[], int maxSize)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return 0;

    int count = 0;
    while (count < maxSize)
    {
        file >> data[count].day;
        file >> data[count].month;
        file >> data[count].amount;
        std::getline(file >> std::ws, data[count].type);

        if (file.fail())
            break;

        count++;
    }

    return count;
}
