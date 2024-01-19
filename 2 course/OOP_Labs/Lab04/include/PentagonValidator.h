#pragma once

#include "IFigureValidator.h"

template<class T>
class PentagonValidator : public IFigureValidator<T> {
public:
    void validate(std::vector<Point<T>>& points) const override {
        if (points.size() != 5) {
            throw std::invalid_argument("Pentagon must have exactly 5 points.");
        }


    }
};