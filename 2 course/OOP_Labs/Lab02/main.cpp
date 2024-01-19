#include <iostream>
#include "FiveDigitArray.h"
#include "outputLab.h"

int main()
{
    std::cout << "Введите два пятиричных числа:" << std::endl;
    std::string num1, num2;
    std::cin >> num1 >> num2;
    tryPerformAllOperation(num1, num2);

    return 0;
}