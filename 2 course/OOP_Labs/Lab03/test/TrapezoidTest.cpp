#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "trapezoid.h" // Подключите заголовочный файл для класса Trapezoid

const double EPSILON=1e9-7;

struct TrapezoidTestParam {
    size_t numVertices;
    std::vector<Point> vertices;
    double expectedArea;
    Point expectedGeomCenter;
};

class TrapezoidTest : public testing::TestWithParam<TrapezoidTestParam> {};

TEST_P(TrapezoidTest, CalculationAreaTest) {
    TrapezoidTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Trapezoid trapezoid(numVertices, vertices);

    double resultArea = trapezoid.CalculationArea();
    double expectedArea=param.expectedArea;
    bool result=resultArea-expectedArea<EPSILON;
    EXPECT_EQ(result, true);
}

TEST_P(TrapezoidTest, CalculationGeomCenterTest) {
    TrapezoidTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Trapezoid trapezoid(numVertices, vertices);

    Point result = trapezoid.CalculationGeomCenter();
    double resultX = result.coordinateX;
    double  resultY = result.coordinateY;
    double  expectedX = param.expectedGeomCenter.coordinateX;
    double  expectedY = param.expectedGeomCenter.coordinateY;
    bool compareX=resultX-expectedX<EPSILON;
    bool compareY=resultX-expectedY<EPSILON;

    EXPECT_EQ(compareX, true);
    EXPECT_EQ(compareY, true);
}

TEST_P(TrapezoidTest, AssignmentOperatorTest) {
    TrapezoidTestParam param = GetParam();
    Trapezoid trapezoid1(param.numVertices, param.vertices);
    Trapezoid trapezoid2;
    trapezoid2 = trapezoid1;

    EXPECT_EQ(trapezoid1, trapezoid2);
}

TEST_P(TrapezoidTest, EqualityOperatorTest) {
    TrapezoidTestParam param = GetParam();
    Trapezoid trapezoid1(param.numVertices, param.vertices);
    Trapezoid trapezoid2(param.numVertices, param.vertices);
    bool result = trapezoid1 == trapezoid2;

    EXPECT_EQ(true, result);
}

INSTANTIATE_TEST_SUITE_P(ParametrizedTrapezoidTests, TrapezoidTest,
    testing::Values(
        TrapezoidTestParam{4, {{1, 1}, {2, 3}, {4, 3}, {5, 1}}, 6.0, {3, 2}}
        
    )
);
