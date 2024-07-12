#include <bits/stdc++.h>

struct Item
{
    char key[6];
    std::string line;
};

void sortLetters(int &digit, Item *tempArray, Item *data, int &size)
{
    int countLetters[26];
    memset(countLetters, 0, sizeof(int) * 26);
    for (int indexElement = 0; indexElement < size; ++indexElement)
    {

        ++countLetters[data[indexElement].key[digit] - 'A'];
    }

    for (int indexElement = 1; indexElement < 26; ++indexElement)
    {
        countLetters[indexElement] += countLetters[indexElement - 1];
    }

    for (int indexElement = size - 1; indexElement >= 0; --indexElement)
    {
        int insertIndex = --countLetters[data[indexElement].key[digit] - 'A'];
        tempArray[insertIndex] = data[indexElement];
    }
}

void sortNumbers(int &digit, Item *tempArray, Item *data, int &size)
{
    int countNums[10];
    memset(countNums, 0, sizeof(int) * 10);
    for (int indexElement = 0; indexElement < size; ++indexElement)
    {

        ++countNums[data[indexElement].key[digit] - '0'];
    }

    for (int indexElement = 1; indexElement < 10; ++indexElement)
    {
        countNums[indexElement] += countNums[indexElement - 1];
    }

    for (int indexElement = size - 1; indexElement >= 0; --indexElement)
    {
        int insertIndex = --countNums[data[indexElement].key[digit] - '0'];
        tempArray[insertIndex] = data[indexElement];
    }
}

int main()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    char inputFirstPart;
    std::string inputSecondPart, inputThirdPart, inputLine;
    inputLine.reserve(64);
    int size = 0, capacity = 64;
    Item *data = new Item[capacity];
    Item inputItem;
    while (std::cin >> inputFirstPart)
    {

        std::cin >> inputSecondPart >> inputThirdPart >> inputLine;
        inputItem.key[0] = inputFirstPart;
        inputItem.key[1] = inputSecondPart[0];
        inputItem.key[2] = inputSecondPart[1];
        inputItem.key[3] = inputSecondPart[2];
        inputItem.key[4] = inputThirdPart[0];
        inputItem.key[5] = inputThirdPart[1];
        inputItem.line = inputLine;
        if (capacity == size)
        {
            capacity *= 2;
            Item *newData = new Item[capacity];
            for (size_t index = 0; index < size; ++index)
            {
                newData[index] = data[index];
            }
            delete[] data;
            data = newData;
        }

        data[size] = inputItem;
        ++size;
    }

    if (size == 0)
    {
        return 0;
    }

    for (int index = 5; index >= 0; --index)
    {
        Item *ans = new Item[size];

        if (isdigit(data[0].key[index]))
        {
            sortNumbers(index, ans, data, size);
        }
        else
        {
            sortLetters(index, ans, data, size);
        }
        delete[] data;
        data = ans;
    }
    for (size_t index = 0; index < size; ++index)
    {
        std::cout << data[index].key[0] << ' ' << data[index].key[1] << data[index].key[2] << data[index].key[3]
                  << ' ' << data[index].key[4] << data[index].key[5] << '\t' << data[index].line << '\n';
    }

    return 0;
}
