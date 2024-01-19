#include "trapezoid.h"
#include <Point.h>
#include <bits/stdc++.h>

Trapezoid::Trapezoid(const size_t &n, std::vector<Point> t)
{
    _points = new Point[n];
    for (size_t i = 0; i < n; ++i)
    {
        _points[i].coordinateX = t[i].coordinateX;
        _points[i].coordinateY = t[i].coordinateY;
    }
    _countPoints = n;
}

Trapezoid::Trapezoid(const Trapezoid &other)
{
    _countPoints = other._countPoints;
    _points = new Point[_countPoints];
    for (size_t i = 0; i < _countPoints; ++i)
    {
        _points[i] = other._points[i];
    }
}

Trapezoid::~Trapezoid()
{
    std::cout << "destructor Trapezoid" << std::endl;
    if (_countPoints > 0)
    {
        _countPoints = 0;
        delete[] _points;
        _points = nullptr;
    }
}

Trapezoid &Trapezoid::operator=(const Trapezoid &other)
{
    if (this == &other)
    {
        return *this; // сделал два return,чтобы не делать большой if
    }
    std::cout << "Copy constructor" << std::endl;
    _countPoints = other._countPoints;
    _points = new Point[_countPoints];

    for (size_t i{0}; i < _countPoints; ++i)
        _points[i] = other._points[i];
    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other)
{
    if (this == &other)
    {
        return *this; // сделал два return,чтобы не делать большой if
    }
    std::cout << "Move constructor" << std::endl;
    _countPoints = other._countPoints;
    _points = other._points;

    other._countPoints = 0;
    other._points = nullptr;
    return *this;
}

bool Trapezoid::operator==(const Trapezoid &other) const
{
    for (size_t i = 0; i < _countPoints; ++i)
    {
        if(_points[i].coordinateX!=other._points[i].coordinateX ||
            _points[i].coordinateY!=other._points[i].coordinateY){
            return false;
        }
    }
    
    return true;
}

std::ostream &Trapezoid::print(std::ostream &output) const
{
    output << "Trapezoid: " << std::endl;
    for (size_t i = 0; i < _countPoints; ++i)
    {
        output << _points[i].coordinateX << " " << _points[i].coordinateY << std::endl;
    }

    return output;
}

std::istream &Trapezoid::read(std::istream &input)
{
    int tempCount;
    input >> tempCount;

    Point *_tempPoints;
    _tempPoints = new Point[tempCount];
    double inputX, inputY;
    for (size_t i = 0; i < tempCount; ++i)
    {
        input >> inputX >> inputY;
        _tempPoints[i].coordinateX = inputX;
        _tempPoints[i].coordinateY = inputY;
    }
    this->_countPoints = tempCount;
    this->_points = _tempPoints;

    return input;
}

Point Trapezoid::CalculationGeomCenter()
{
    Point geomCenter;
    double sumX = 0;
    double sumY = 0;
    for (size_t i = 0; i < _countPoints; ++i)
    {
        sumX += _points[i].coordinateX;
        sumY += _points[i].coordinateY;
    }

    geomCenter.coordinateX = sumX / _countPoints;
    geomCenter.coordinateY = sumY / _countPoints;

    return geomCenter;
}

double CalculateDistanceTrapezoid(const Point &p1, const Point &p2)
{
    double dx = std::abs(p2.coordinateX - p1.coordinateX);
    double dy = std::abs(p2.coordinateY - p1.coordinateY);
    return std::sqrt(dx * dx + dy * dy);
}

double Trapezoid::CalculationArea() const
{
    // рассматриваем только равнобедренную трапецию
    const double epsilon = 1e-9;
    double heightLowerBase = _points[0].coordinateY;
    double heightUpperBase = _points[0].coordinateY;

    for (size_t i = 0; i < _countPoints; ++i)
    {
        if (_points[i].coordinateY < heightLowerBase)
        {
            heightLowerBase = _points[i].coordinateY;
        }
        else if (_points[i].coordinateY > heightUpperBase)
        {
            heightUpperBase = _points[i].coordinateY;
        }
    }
    double heightTrapezoid = heightUpperBase - heightLowerBase;

    std::vector<double> SidesTrapezoid;
    SidesTrapezoid.push_back(CalculateDistanceTrapezoid(_points[0], _points[1]));
    SidesTrapezoid.push_back(CalculateDistanceTrapezoid(_points[1], _points[2]));
    SidesTrapezoid.push_back(CalculateDistanceTrapezoid(_points[2], _points[3]));
    SidesTrapezoid.push_back(CalculateDistanceTrapezoid(_points[3], _points[0]));
    size_t i, j;
    bool flagBreak=true;
    for (i = 0; i < _countPoints-1; ++i)
    {
        for (j = i+1; j < _countPoints; ++j)
        {
            if (std::abs(SidesTrapezoid[i] - SidesTrapezoid[j]) < epsilon)
            {
                flagBreak=false;
                break;
            }
        }
        if (!flagBreak){
            break;
        }
        
    }
    double LengthSumBase = 0;
    for (size_t newIndex = 0; newIndex < _countPoints; ++newIndex)
    {
        if (newIndex != i && newIndex != j)
        {
            LengthSumBase+=SidesTrapezoid[newIndex];
        }
    }

    double area = LengthSumBase*heightTrapezoid*0.5;
    return area;
}
