#pragma once

#include "Figure.h"
#include "FigureValidator.h"
#include "TrapezoidValidator.h"

template <ScalarType T>
class Trapezoid : public Figure<T>
{
public:
    Trapezoid() = default;

    Trapezoid(const std::vector<Point<T>> &points)
    {
        TrapezoidValidator<T> TrapezoidValidator;
        FigureValidator<T>::validateFigure(static_cast<const IFigureValidator<T> *>(&TrapezoidValidator), points);
        this->_points = points;
    }

    Trapezoid<T> &operator=(const Figure<T> &other) override
    {
        if (this != &other)
        {
            const Trapezoid *otherTrapezoid = dynamic_cast<const Trapezoid *>(&other);
            if (otherTrapezoid)
            {
                this->_points.clear();
                this->_points = other.getPoints();
            }
            else
            {
                throw std::invalid_argument("Invalid assignment. Expected Figure to be a Pentagon.");
            }
        }
        return *this;
    }

    Trapezoid<T> &operator=(Figure<T> &&other) override
    {
        Trapezoid *otherTrapezoid = dynamic_cast<Trapezoid *>(&other);
        if (otherTrapezoid)
        {
            this->_points = std::move(otherTrapezoid->_points);
        }
        else
        {
            throw std::invalid_argument("Invalid move assignment. Expected Figure to be a Pentagon.");
        }

        return *this;
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Trapezoid *otherTrapezoid = dynamic_cast<const Trapezoid *>(&other);
        if (otherTrapezoid)
        {
            return this->_points == otherTrapezoid->_points;
        }
        return false;
    }

    std::istream &operator>>(std::istream &input) override
    {
        this->_points.clear();
        for (int i = 0; i < 6; ++i)
        {
            Point<T> point;
            input >> point;
            this->_points.push_back(point);
        }
        TrapezoidValidator<T> validator;
        FigureValidator<T>::validateFigure(static_cast<const IFigureValidator<T> *>(&validator), this->_points);
        return input;
    }

    double area() const override
    {
        double area = 0.0;

        for (int i{0}; i < 2; ++i)
        {
            area += this->triangleArea(this->_points[0], this->_points[i + 1], this->_points[i + 2]);
        }

        return area;
    }

    Point<T> getCenter() const override
    {

        double centerX = 0.0;
        double centerY = 0.0;

        for (const Point<T> &point : this->_points)
        {
            centerX += point.getX();
            centerY += point.getY();
        }

        centerX /= 4.0;
        centerY /= 4.0;

        return Point<T>(centerX, centerY);
    }

    Figure<T> *createFigureWithPoints(const std::vector<Point<T>> &points) const override
    {
        TrapezoidValidator<T> TrapezoidValidator;
        FigureValidator<T>::validateFigure(static_cast<const IFigureValidator<T> *>(&TrapezoidValidator), points);
        return new Trapezoid<T>(points);
    }
};