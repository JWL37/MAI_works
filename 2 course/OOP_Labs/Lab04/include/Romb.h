#pragma once

#include "Figure.h"
#include "FigureValidator.h"
#include "RombValidator.h"

template<ScalarType T>
class Romb : public Figure<T> {
public:
    Romb() = default;

    Romb(const std::vector<Point<T>>& points) : Figure<T>(points) {
        RombValidator<T> RombValidator;
        FigureValidator<T>::validateFigure(static_cast<const IFigureValidator<T>*> (&RombValidator), points);
        this->_points = points;
    }

    Romb<T>& operator=(const Figure <T>& other) override {
        if (this != &other) {
            const auto* otherRomb = dynamic_cast<const Romb*>(&other);
            if (otherRomb) {
                this->_points.clear();
                this->_points = other.getPoints();
            } else {
                throw std::invalid_argument("Invalid assignment. Expected Figure to be a Pentagon.");
            }
        }
        return *this;
    }

    Romb<T>& operator=(Figure <T>&& other) override {
        Romb* otherRomb = dynamic_cast<Romb*>(&other);
        if (otherRomb) {
            this->_points = std::move(otherRomb->_points);
        } else {
            throw std::invalid_argument("Invalid move assignment. Expected Figure to be a Pentagon.");
        }

        return *this;
    }

    bool operator==(const Figure <T>& other) const override {
        const Romb* otherRomb = dynamic_cast<const Romb*>(&other);
        if (otherRomb) {
            return this->_points == otherRomb->_points;
        }
        return false;
    }

    std::istream& operator>>(std::istream& input) override {
        this->_points.clear();
        for (int i = 0; i < 8; ++i) {
            Point<T> point;
            input >> point;
            this->_points.push_back(point);
        }
        RombValidator<T> validator;
        FigureValidator<T>::validateFigure(static_cast<const IFigureValidator<T>*> (&validator), this->_points);
        return input;
    }

    double area() const override {
        double area = 0.0;

        for (int i{0}; i < 2; ++i) {
            area += this->triangleArea(this->_points[0], this->_points[i + 1], this->_points[i + 2]);
        }

        return area;
    }

    Point<T> getCenter() const override {
        double centerX = 0.0;
        double centerY = 0.0;

        for (const Point<T>& point: this->_points) {
            centerX += point.getX();
            centerY += point.getY();
        }

        centerX /= 4.0;
        centerY /= 4.0;

        return Point<T>(centerX, centerY);
    }


    Figure<T>* createFigureWithPoints(const std::vector<Point<T>>& points) const override {
        RombValidator<T> RombValidator;
        FigureValidator<T>::validateFigure(static_cast<const IFigureValidator<T>*> (&RombValidator), points);
        return new Romb<T>(points);
    }
};