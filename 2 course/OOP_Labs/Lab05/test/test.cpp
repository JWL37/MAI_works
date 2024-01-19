#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include <MyQueue.h>

class isEmptyParameterizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, bool>>
{
};

TEST_P(isEmptyParameterizedTest, CheckIsEquals)
{
    std::vector<int> testData = std::get<0>(GetParam());
    MyQueue<int, 6> queueTest;
    for (size_t i = 0; i < testData.size(); i++)
    {
        queueTest.push(testData[i]);
    }

    bool expected = std::get<1>(GetParam());
    bool result = queueTest.isEmpty();
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    isEmptyTests,
    isEmptyParameterizedTest,
    ::testing::Values(
        std::make_tuple(std::vector<int>{1, 2, 3}, false),
        std::make_tuple(std::vector<int>{}, true),
        std::make_tuple(std::vector<int>{1, 2, 3, 5, 6}, false)));

class isFullParameterizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, bool>>
{
};

TEST_P(isFullParameterizedTest, CheckIsEquals)
{
    std::vector<int> testData = std::get<0>(GetParam());
    MyQueue<int, 6> queueTest;
    for (size_t i = 0; i < testData.size(); i++)
    {
        queueTest.push(testData[i]);
    }

    bool expected = std::get<1>(GetParam());
    bool result = queueTest.isFull();
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    isFullTests,
    isFullParameterizedTest,
    ::testing::Values(
        std::make_tuple(std::vector<int>{1, 2, 3}, false),
        std::make_tuple(std::vector<int>{}, false),
        std::make_tuple(std::vector<int>{1, 2, 3, 5, 6, 7}, true)));

TEST(MyQueueTest, PushWhenFull)
{
    MyQueue<int, 5> queueTest;

    for (int i = 0; i < 5; ++i)
    {
        queueTest.push(i);
    }

    EXPECT_THROW(queueTest.push(42), std::overflow_error);
}

TEST(MyQueueTest, PopWhenEmpty)
{
    MyQueue<int, 5> queueTest;

    EXPECT_THROW(queueTest.pop(), std::underflow_error);
}

TEST(MyQueueTest, FrontWhenEmpty)
{
    MyQueue<int, 5> queueTest;

    EXPECT_THROW(queueTest.pop(), std::underflow_error);
}

class FrontParameterizedTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, int>>
{
};

TEST_P(FrontParameterizedTest, CheckIsEquals)
{
    std::vector<int> testData = std::get<0>(GetParam());
    MyQueue<int, 6> queueTest;
    for (size_t i = 0; i < testData.size(); i++)
    {
        queueTest.push(testData[i]);
    }

    int expected = std::get<1>(GetParam());
    int result = queueTest.front();
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    FrontTests,
    FrontParameterizedTest,
    ::testing::Values(
        std::make_tuple(std::vector<int>{1, 2, 3}, 1),
        std::make_tuple(std::vector<int>{21}, 21),
        std::make_tuple(std::vector<int>{0, 2, 3, 4,5}, 0)));


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
