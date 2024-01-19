#pragma once

#include <string>
#include <iostream>

class FiveDigitArray
{
public:
    FiveDigitArray();
    FiveDigitArray(const size_t &n, unsigned char symbol = 0);
    FiveDigitArray(const std::initializer_list<unsigned char> &listNum);
    FiveDigitArray(const std::string &lineNum);
    FiveDigitArray(const FiveDigitArray &other);
    FiveDigitArray(FiveDigitArray &&other) noexcept;

    int toDecimal();
    FiveDigitArray decimalToFiveDigit(int &decimalValue);
    FiveDigitArray &operator=(const FiveDigitArray &other);
    FiveDigitArray operator+(FiveDigitArray &other);
    FiveDigitArray operator-(FiveDigitArray &other);
    bool operator==(const FiveDigitArray &other) const;
    bool operator>(FiveDigitArray &other);
    bool operator<(FiveDigitArray &other);
    std::ostream &print(std::ostream &os);

    size_t get_size();
    std::string get_array();
    virtual ~FiveDigitArray() noexcept;

private:
    size_t _size;
    unsigned char *_array;
};
