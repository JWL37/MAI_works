#include "FiveDigitArray.h"
#include <iostream>

FiveDigitArray::FiveDigitArray() : _size(0), _array{nullptr}
{
    // std::cout << "Default constructor" << std::endl;
}

FiveDigitArray::FiveDigitArray(const size_t &n, unsigned char symbol)
{
    _array = new unsigned char[n];
    for (size_t i = 0; i < n; ++i)
        _array[i] = symbol;
    _size = n;
}

FiveDigitArray::FiveDigitArray(const std::initializer_list<unsigned char> &listNum)
{
    _array = new unsigned char[listNum.size()];
    size_t i{0};
    for (auto elem : listNum)
    {
        _array[i++] = elem;
    }
    _size = listNum.size();
}

FiveDigitArray::FiveDigitArray(const std::string &lineNum)
{
    _array = new unsigned char[lineNum.size()];
    _size = lineNum.size();

    for (size_t i{0}; i < _size; ++i)
        _array[i] = lineNum[i];
}

FiveDigitArray::FiveDigitArray(const FiveDigitArray &other)
{
    std::cout << "Copy constructor" << std::endl;
    _size = other._size;
    _array = new unsigned char[_size];

    for (size_t i{0}; i < _size; ++i)
        _array[i] = other._array[i];
}

FiveDigitArray::FiveDigitArray(FiveDigitArray &&other) noexcept
{
    std::cout << "Move constructor" << std::endl;
    _size = other._size;
    _array = other._array;

    other._size = 0;
    other._array = nullptr;
}

std::ostream &FiveDigitArray::print(std::ostream &os)
{
    for (size_t i = 0; i < _size; ++i)
        os << _array[i];
    return os;
}
FiveDigitArray FiveDigitArray::decimalToFiveDigit(int &decimalValue)
{
    if (decimalValue < 0)
    {
        throw std::invalid_argument("Decimal value must be non-negative");
    }

    if (decimalValue == 0)
    {
        return FiveDigitArray(1, '0');
    }

    std::string result;
    while (decimalValue > 0)
    {
        result.insert(result.begin(), '0' + (decimalValue % 5));
        decimalValue /= 5;
    }
    return FiveDigitArray(result);
}

int FiveDigitArray::toDecimal()
{
    int decimalValue = 0;
    int power = 1;

    for (int i = _size - 1; i >= 0; --i)
    {
        if (_array[i] >= '0' && _array[i] <= '4')
        {
            decimalValue += (_array[i] - '0') * power;
            power *= 5;
        }
        else
        {
            throw std::invalid_argument("Invalid character in the five-digit array");
        }
    }

    return decimalValue;
}
FiveDigitArray &FiveDigitArray::operator=(const FiveDigitArray &other)
{
    if (this != &other)
    {

        if (_size > 0)
        {
            delete[] _array;
            _size = 0;
            _array = nullptr;
        }

        _size = other._size;
        _array = new unsigned char[_size];

        for (size_t i = 0; i < _size; ++i)
        {
            _array[i] = other._array[i];
        }
    }

    return *this;
}
FiveDigitArray FiveDigitArray::operator+(FiveDigitArray &other)
{

    int thisDecimal = toDecimal();

    int otherDecimal = other.toDecimal();

    int sumDecimal = thisDecimal + otherDecimal;

    return decimalToFiveDigit(sumDecimal);
}
FiveDigitArray FiveDigitArray::operator-(FiveDigitArray &other)
{
    int thisDecimal = toDecimal();

    int otherDecimal = other.toDecimal();

    int subtractDecimal = thisDecimal - otherDecimal;

    return decimalToFiveDigit(subtractDecimal);
}

bool FiveDigitArray::operator==(const FiveDigitArray &other) const
{
    bool isEqual = true;
    if (_size != other._size)
    {
        isEqual = false;
        return isEqual;
    }
    else
    {
        for (int i = 0; i < _size; ++i)
        {
            if (_array[i] != other._array[i])
            {
                isEqual = false;
                break;
            }
        }
    }
    return isEqual;
}
bool FiveDigitArray::operator>(FiveDigitArray &other)
{
    int thisDecimal = toDecimal();
    int otherDecimal = other.toDecimal();
    return thisDecimal > otherDecimal;
}
bool FiveDigitArray::operator<(FiveDigitArray &other)
{
    int thisDecimal = toDecimal();
    int otherDecimal = other.toDecimal();
    return thisDecimal < otherDecimal;
}

size_t FiveDigitArray::get_size()
{
    return _size;
}
std::string FiveDigitArray::get_array()
{
    std::string str_array = "";
    for (size_t i = 0; i < _size; ++i)
    {
        str_array.push_back(_array[i]);
    }

    return str_array;
}

FiveDigitArray::~FiveDigitArray() noexcept
{
    if (_size > 0)
    {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}
