#ifndef PENTAGON_H
#define PENTAGON_H
#include <bits/stdc++.h>
#include "Point.h"
#include "Figure.h"

class Pentagon : public Figure
{
public:
    Pentagon() = default;
    Pentagon(const size_t &n, std::vector<Point> t);
    Pentagon(const Pentagon &other);
    virtual ~Pentagon();
    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other);
    bool operator==(const Pentagon &other) const;
    std::ostream &print(std::ostream &output) const override;
    std::istream &read(std::istream &input) override;
    Point CalculationGeomCenter() override;
    double CalculationArea() const override;
    static Pentagon CreateInstance(std::vector<Point> points) {

      return Pentagon(points.size(),points);
    }
protected:
    size_t _countPoints;
    Point *_points;
};

static bool validatePentagon(std::vector<Point> points);

#endif // PENTAGON_H