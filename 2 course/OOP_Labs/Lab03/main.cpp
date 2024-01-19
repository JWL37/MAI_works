#include <bits/stdc++.h>
#include <Point.h>
#include <Figure.h>
#include <rhomb.h>
#include <trapezoid.h>
#include <pentagon.h>

int main()
{
    Rhomb figure0;
    Rhomb figure1;
    std::cout<<"Введите cначала количество точек, а потом координаты точек для создания ромба:"<<std::endl; 
    std::cin>>figure0;//4 \n 0 0 \n 3 4 \n 8 4 \n 5 0 
    std::cout<<figure0;
    figure1=figure0;
    std::cout<<'\n';
    std::vector<Point> points{Point(1, 1), Point(2, 3), Point(4, 3), Point(5, 1)};
    Trapezoid  figure2=Trapezoid::CreateInstance(points);
    std::cout<<"Введите cначала количество точек, а потом координаты точек для создания пятиугольника:"<<std::endl; 
    Pentagon figure3;
    std::cin>>figure3;
    std::cout<<figure3;
    std::cout<<'\n';
    Figure* figures[] {&figure0,&figure2,&figure3};
    std::cout<<sizeof(figures)/sizeof(figure0)<<std::endl;
    double allArea=0;

    for(auto &f :figures){
        Point GeomCenter;
        GeomCenter=f->CalculationGeomCenter();
        std::cout<<GeomCenter.coordinateX<<" "<<GeomCenter.coordinateY<<std::endl;
        std::cout<<f->CalculationArea()<<std::endl;
        allArea+=f->CalculationArea();
    }
    std::cout<<allArea<<std::endl;
    


    return 0;

}