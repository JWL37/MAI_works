#pragma once

#include "Figure.h"

template<ScalarType T>
class IFigureValidator {
public:
    virtual void validate(std::vector<Point<T>>& points) const = 0;
    
};