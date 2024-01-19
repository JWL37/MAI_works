#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "rhomb.h"

struct RhombTestParam {
    size_t numVertices;
    std::vector<Point> vertices;
    double expectedArea;
    Point expectedGeomCenter;
};

class RhombTest : public testing::TestWithParam<RhombTestParam> {};

TEST_P(RhombTest, CalculationAreaTest) {
    RhombTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Rhomb rhomb(numVertices, vertices);

    double resultArea = rhomb.CalculationArea();
    double expectedArea=param.expectedArea;
    EXPECT_DOUBLE_EQ(resultArea, expectedArea);
}

TEST_P(RhombTest, CalculationGeomCenterTest) {
    RhombTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Rhomb rhomb(numVertices, vertices);

    Point result = rhomb.CalculationGeomCenter();
    double resultX=result.coordinateX;
    double resultY=result.coordinateY;
    double expectedX=param.expectedGeomCenter.coordinateX;
    double expectedY=param.expectedGeomCenter.coordinateY;
    EXPECT_EQ(resultX, expectedX);
    EXPECT_EQ(resultY, expectedY);

}

TEST_P(RhombTest, AssignmentOperatorTest) {
    RhombTestParam param = GetParam();
    Rhomb rhomb1(param.numVertices, param.vertices);
    Rhomb rhomb2;
    rhomb2 = rhomb1;

    EXPECT_EQ(rhomb1, rhomb2);
}

TEST_P(RhombTest, EqualityOperatorTest) {
    RhombTestParam param = GetParam();
    Rhomb rhomb1(param.numVertices, param.vertices);
    Rhomb rhomb2(param.numVertices, param.vertices);
    bool result=rhomb1==rhomb2;

    EXPECT_EQ(true, result);
}

TEST_P(RhombTest, ConstructorTest) {
    RhombTestParam param = GetParam();

    size_t numVertices = param.numVertices;
    std::vector<Point> vertices = param.vertices;
    Rhomb rhomb(numVertices, vertices);
    int result=rhomb.getCountPoints();
    EXPECT_EQ(result, numVertices);
}

INSTANTIATE_TEST_SUITE_P(ParametrizedRhombTests, RhombTest,
    testing::Values(
        RhombTestParam{4, {{0, 0}, {3, 4}, {8, 4}, {5, 0}}, 20.0, {4, 2}},
        RhombTestParam{4, {{0, 0}, {0, 2}, {2, 2}, {2, 0}}, 4.0, {1, 1}}
    )
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
