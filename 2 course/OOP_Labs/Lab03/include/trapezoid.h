#ifndef Trapezoid_H
#define Trapezoid_H
#include <bits/stdc++.h>
#include "Point.h"
#include "Figure.h"

class Trapezoid : public Figure
{
public:
    Trapezoid() = default;
    Trapezoid(const size_t &n, std::vector<Point> t);
    Trapezoid(const Trapezoid &other);

    virtual ~Trapezoid();
    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other);
    bool operator==(const Trapezoid &other) const;
    std::ostream &print(std::ostream &output) const override;
    std::istream &read(std::istream &input) override;
    Point CalculationGeomCenter() override;
    double CalculationArea() const override;
    static Trapezoid CreateInstance(std::vector<Point> points) {

      return Trapezoid(points.size(),points);
    }
protected:
    size_t _countPoints;
    Point *_points;
};

#endif // Trapezoid_H