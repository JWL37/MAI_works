#include "outputLab.h"
#include <iostream>
#include "FiveDigitArray.h"

void checkCorrectInput(std::string num1, std::string num2)
{
    for (char &elem : num1)
    {
        if (elem < '0' or elem > '4')
        {
            throw std::invalid_argument("Invalid character in the five-digit array");
        }
    }
    for (char &elem : num2)
    {
        if (elem < '0' or elem > '4')
        {
            throw std::invalid_argument("Invalid character in the five-digit array");
        }
    }
}


void tryPerformAllOperation(std::string num1,std::string num2){
    try
    {
        checkCorrectInput(num1,num2);
    }
    catch(const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
    FiveDigitArray first(num1);
    FiveDigitArray second(num2);
    FiveDigitArray resultSum=first+second;
    std::cout<<"Сумма : ";
    resultSum.print(std::cout)<<std::endl;

    FiveDigitArray resultSubtract;
    if (num1==num2){
        std::cout<<"первое число равно второму"<<std::endl;
        resultSubtract=first-second;
    }
    else if (num1>num2){
        std::cout<<"первое число больше второго"<<std::endl;
        resultSubtract=first-second;
    }
    else if (num1<num2){
        std::cout<<"первое число меньше второго"<<std::endl;
        resultSubtract=second-first;
    }
    
    std::cout<<"Вычитание : ";
    resultSubtract.print(std::cout)<<std::endl;
}