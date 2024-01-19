#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "pentagon.h" 

const double EPSILON=1e9-7;
struct PentagonTestParam {
    size_t numVertices;
    std::vector<Point> vertices;
    double expectedArea;
    Point expectedGeomCenter;
};

class PentagonTest : public testing::TestWithParam<PentagonTestParam> {};

TEST_P(PentagonTest, CalculationAreaTest) {
    PentagonTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Pentagon pentagon(numVertices, vertices);

    double resultArea = pentagon.CalculationArea();
    double expectedArea=param.expectedArea;
    bool compareArea=resultArea-expectedArea<EPSILON;
    EXPECT_DOUBLE_EQ(compareArea, true);
}

TEST_P(PentagonTest, CalculationGeomCenterTest) {
    PentagonTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Pentagon pentagon(numVertices, vertices);

    Point result = pentagon.CalculationGeomCenter();

    double resultX = result.coordinateX;
    double  resultY = result.coordinateY;
    double  expectedX = param.expectedGeomCenter.coordinateX;
    double  expectedY = param.expectedGeomCenter.coordinateY;
    bool compareX=resultX-expectedX<EPSILON;
    bool compareY=resultX-expectedY<EPSILON;

    EXPECT_EQ(compareX, true);
    EXPECT_EQ(compareY, true);
}

TEST_P(PentagonTest, AssignmentOperatorTest) {
    PentagonTestParam param = GetParam();
    Pentagon pentagon1(param.numVertices, param.vertices);
    Pentagon pentagon2;
    pentagon2 = pentagon1;

    EXPECT_EQ(pentagon1, pentagon2);
}

TEST_P(PentagonTest, EqualityOperatorTest) {
    PentagonTestParam param = GetParam();
    Pentagon pentagon1(param.numVertices, param.vertices);
    Pentagon pentagon2(param.numVertices, param.vertices);
    bool result = pentagon1 == pentagon2;

    EXPECT_EQ(true, result);
}

INSTANTIATE_TEST_SUITE_P(ParametrizedPentagonTests, PentagonTest,
    testing::Values(
        PentagonTestParam{5, {{-2.9, -4.5}, {-4.7, 1.05}, {0, 4.5}, {4.7, 1.05}, {2.9, -4.5}}, 139.3, {8.8817841970012528e-17, -0.48}}   
    )
);
