#ifndef FIGURE_H
#define FIGURE_H
#include <bits/stdc++.h>
#include <Point.h>

class Figure
{
public:
    Figure() = default;
    virtual ~Figure() = default;
    virtual Figure & operator=(const Figure &other)=default;
    virtual Figure & operator=(Figure &&other)=default;
    virtual bool operator==(const Figure &other) const = default;
    friend std::ostream& operator<<(std::ostream& output, const Figure& Figure) {
        return Figure.print(output);
    }
    virtual std::ostream& print(std::ostream& output) const = 0;

    friend std::istream& operator>>(std::istream& input, Figure& figure) {
        return figure.read(input);
    }
    virtual std::istream& read(std::istream& input) = 0;
   

    operator double() {
        return CalculationArea();
    }
     virtual double CalculationArea() const = 0;

    virtual Point CalculationGeomCenter()=0;


};

#endif // FIGURE_H