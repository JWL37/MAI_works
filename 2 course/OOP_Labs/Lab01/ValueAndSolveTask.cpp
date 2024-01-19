#include <iostream>
#include "ValueAndSolveTask.h"

std::string trySwapAtoBorBtoA(std::string line)
{
    try
    {
        return swapAtoBorBtoA(line);
    }
    catch (const std::invalid_argument &e)
    {
        return e.what();
    }
}

bool isCorrectLine(std::string line)
{
    for (char elemLine : line)
    {
        if (elemLine != 'a' 
            and elemLine != 'b' 
            and elemLine != 'c')
        {
            return false;
        }
    }
    return true;
}

std::string swapAtoBorBtoA(std::string line)
{
    if (!isCorrectLine(line))
        throw std::invalid_argument("Received another symbol!!!");
    std::string result_line{""};
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == 'a')
        {
            line[i] = 'b';
        }
        else if (line[i] == 'b')
        {
            line[i] = 'a';
        }
    }
    return line;
}