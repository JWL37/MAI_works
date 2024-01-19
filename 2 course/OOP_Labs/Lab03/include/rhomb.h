#ifndef RHOMB_H
#define RHOMB_H
#include <bits/stdc++.h>
#include "Point.h"
#include "Figure.h"

class Rhomb : public Figure
{
public:
    Rhomb() = default;
    Rhomb(const size_t &n, std::vector<Point> t);
    virtual ~Rhomb();
    Rhomb &operator=(const Rhomb &other);
    Rhomb &operator=(Rhomb &&other);
    bool operator==(const Rhomb &other) const;
    std::ostream &print(std::ostream &output) const override;
    std::istream &read(std::istream &input) override;
    Point CalculationGeomCenter() override;
    double CalculationArea() const override;

    size_t getCountPoints() const { return _countPoints; }
    std::vector<Point> getPoints();
    static Rhomb CreateInstance(std::vector<Point> points)
    {

        return Rhomb(points.size(), points);
    }

protected:
    size_t _countPoints;
    Point *_points;
};

static bool validateRhomb(std::vector<Point> points);

#endif // RHOMB_H