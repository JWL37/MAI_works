#pragma once

#include "IFigureValidator.h"

template<class T>
class TrapezoidValidator : public IFigureValidator<T> {
public:
    void validate(std::vector<Point<T>>& points) const override{
        if (points.size() != 4) {
            throw std::invalid_argument("Trapezoid must have exactly 4 points.");
        }


    }
};