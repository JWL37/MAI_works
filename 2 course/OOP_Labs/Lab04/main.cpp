#include <bits/stdc++.h>
#include "Figure.h"
#include "Pentagon.h"
#include "Trapezoid.h"
#include "Romb.h"
#include "Array.h"

using namespace std;

int main() {
    std::vector<Point<double>> pentagonPoints = {Point(0.0, 0.0), Point(1.0, 0.0), Point(1.5, 1.0), Point(0.5, 2.0),
                                                 Point(0.0, 1.0)};
    std::vector<Point<double>> trapezoidPoints = {Point(0.0, 0.0), Point(6.0, 0.0), Point(4.0, 4.0), Point(2.0, 4.0)};
    std::vector<Point<double>> rombPoints = {Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0), Point(0.0, 2.0)};


    const shared_ptr<Figure<double>> pentagon = make_shared<Pentagon<double>>(pentagonPoints);
    const shared_ptr<Figure<double>> trapezoid = make_shared<Trapezoid<double>>(trapezoidPoints);
    const shared_ptr<Figure<double>> romb = make_shared<Romb<double>>(rombPoints);
    myArray<shared_ptr<Figure<double>>> array;

    array.push_back(pentagon);
    array.push_back(trapezoid);
    array.push_back(romb);

    for (shared_ptr<Figure<double>>& elem : array) {

        cout << "Area: " << static_cast<double>(*elem) << endl;
        cout << "Center: " << elem->getCenter() << endl;

        for (Point<double> point : elem->getPoints()) {
            cout << point << endl;
        }

    }

    cout << array.length() << endl;

    array.remove(1);

    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"после удаления трапеции"<<endl;
    for (shared_ptr<Figure<double>>& elem : array) {

        cout << "Area: " << static_cast<double>(*elem) << endl;
        cout << "Center: " << elem->getCenter() << endl;

        for (Point<double> point : elem->getPoints()) {
            cout << point << endl;
        }

    }

    cout << array.length() << endl;

    return 0;
}