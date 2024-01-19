#include "pentagon.h"

Pentagon::Pentagon(const size_t &n, std::vector<Point> t)
{
    _points = new Point[n];
    for (size_t i = 0; i < n; ++i)
    {
        _points[i].coordinateX = t[i].coordinateX;
        _points[i].coordinateY = t[i].coordinateY;
    }
    _countPoints = n;
}
Pentagon::Pentagon(const Pentagon &other)
{
    _countPoints = other._countPoints;
    _points = new Point[_countPoints];
    for (size_t i = 0; i < _countPoints; ++i)
    {
        _points[i] = other._points[i];
    }
}

Pentagon::~Pentagon()
{
    std::cout << "destructor Pentagon" << std::endl;
    if (_countPoints > 0)
    {
        _countPoints = 0;
        delete[] _points;
        _points = nullptr;
    }
}

Pentagon &Pentagon::operator=(const Pentagon &other)
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

Pentagon &Pentagon::operator=(Pentagon &&other)
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

bool Pentagon::operator==(const Pentagon &other) const
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

std::ostream &Pentagon::print(std::ostream &output) const
{
    output << "Pentagon: " << std::endl;
    for (size_t i = 0; i < _countPoints; ++i)
    {
        output << _points[i].coordinateX << " " << _points[i].coordinateY << std::endl;
    }

    return output;
}

std::istream &Pentagon::read(std::istream &input)
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

Point Pentagon::CalculationGeomCenter()
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

double CalculateDistancePentagon(const Point &p1, const Point &p2)
{
    double dx = std::abs(p2.coordinateX - p1.coordinateX);
    double dy = std::abs(p2.coordinateY - p1.coordinateY);
    return std::sqrt(dx * dx + dy * dy);
}

double Pentagon::CalculationArea() const
{
    const double angle = M_PI / 5;
    const double cotangentValue = 1 / tan(angle);
    double sidePentagon =CalculateDistancePentagon(_points[0],_points[1]);
    double area=1.25*cotangentValue*(sidePentagon*sidePentagon);
    return area;
}

bool validatePentagon(std::vector<Point> points)
{
     if(points.size()!=5){
        throw std::invalid_argument("Введенные точки не образуют ромб");
    }
    const double epsilon=1e9-7;
    std::vector<double> distances;
    double distance1 =std::sqrt(std::pow(points[0].coordinateX- points[1].coordinateX, 2) +
                                        std::pow(points[0].coordinateY - points[1].coordinateY, 2));
    double distance2 =std::sqrt(std::pow(points[1].coordinateX- points[2].coordinateX, 2) +
                                        std::pow(points[1].coordinateY - points[2].coordinateY, 2));
    double distance3 =std::sqrt(std::pow(points[2].coordinateX- points[3].coordinateX, 2) +
                                        std::pow(points[2].coordinateY - points[3].coordinateY, 2));
    double distance4 =std::sqrt(std::pow(points[3].coordinateX- points[4].coordinateX, 2) +
                                        std::pow(points[3].coordinateY - points[4].coordinateY, 2));
    double distance5 =std::sqrt(std::pow(points[4].coordinateX- points[0].coordinateX, 2) +
                                        std::pow(points[4].coordinateY - points[0].coordinateY, 2));
    if (distance1==distance2 && distance2==distance3 && distance3==distance4 && distance4==distance1 && distance5==distance1){
        return true;
    }
    throw std::invalid_argument("Введенные точки не образуют ромб");
}
