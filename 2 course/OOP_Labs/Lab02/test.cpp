#include <gtest/gtest.h>
#include "FiveDigitArray.h"

class isEqualParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>>
{
};

TEST_P(isEqualParameterizedTest, CheckIsEquals)
{
    FiveDigitArray first(std::get<0>(GetParam()));
    FiveDigitArray second(std::get<1>(GetParam()));
    bool expected = std::get<2>(GetParam());
    bool result = first == second;
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    isEqualTests,
    isEqualParameterizedTest,
    ::testing::Values(
        std::make_tuple("23", "13", false),
        std::make_tuple("10", "14", false),
        std::make_tuple("214", "214", true),
        std::make_tuple("0", "0", true)));

class isMoreParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>>
{
};

TEST_P(isMoreParameterizedTest, CheckIsMore)
{
    FiveDigitArray first(std::get<0>(GetParam()));
    FiveDigitArray second(std::get<1>(GetParam()));
    bool expected = std::get<2>(GetParam());
    bool result = first > second;
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    isMoreTests,
    isMoreParameterizedTest,
    ::testing::Values(
        std::make_tuple("23", "13", true),
        std::make_tuple("10", "14", false),
        std::make_tuple("214", "214", false)));

class isLessParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>>
{
};

TEST_P(isLessParameterizedTest, CheckIsMore)
{
    FiveDigitArray first(std::get<0>(GetParam()));
    FiveDigitArray second(std::get<1>(GetParam()));
    bool expected = std::get<2>(GetParam());
    bool result = first < second;
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    isLessTests,
    isLessParameterizedTest,
    ::testing::Values(
        std::make_tuple("23", "13", false),
        std::make_tuple("10", "14", true),
        std::make_tuple("214", "214", false)));

class sumFiveParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>>
{
};

TEST_P(sumFiveParameterizedTest, CheckSumFive)
{
    FiveDigitArray first(std::get<0>(GetParam()));
    FiveDigitArray second(std::get<1>(GetParam()));
    FiveDigitArray expected(std::get<2>(GetParam()));
    FiveDigitArray result = first + second;
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    sumFiveTests,
    sumFiveParameterizedTest,
    ::testing::Values(
        std::make_tuple("21", "31", "102"),
        std::make_tuple("10", "14", "24"),
        std::make_tuple("0", "0", "0"),
        std::make_tuple("2", "3", "10")));

class subtractFiveParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>>
{
};

TEST_P(subtractFiveParameterizedTest, CheckSubtractFive)
{
    FiveDigitArray first(std::get<0>(GetParam()));
    FiveDigitArray second(std::get<1>(GetParam()));
    FiveDigitArray expected(std::get<2>(GetParam()));
    FiveDigitArray result = first - second;
    ASSERT_EQ(expected, result);
}

INSTANTIATE_TEST_CASE_P(
    subtractFiveTests,
    subtractFiveParameterizedTest,
    ::testing::Values(
        std::make_tuple("14", "14", "0"),
        std::make_tuple("0", "0", "0"),
        std::make_tuple("12", "3", "4")));

class getSizeFiveParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, size_t>>
{
};

TEST_P(getSizeFiveParameterizedTest, CheckGetSizeFive)
{
    FiveDigitArray fiveDigitArray_(std::get<0>(GetParam()));
    size_t expected_size = std::get<1>(GetParam());
    size_t result = fiveDigitArray_.get_size();
    ASSERT_EQ(expected_size, result);
}

INSTANTIATE_TEST_CASE_P(
    getSizeFiveTests,
    getSizeFiveParameterizedTest,
    ::testing::Values(
        std::make_tuple("1431242413", 10),
        std::make_tuple("0", 1),
        std::make_tuple("123", 3)));

class getArrayFiveParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
};

TEST_P(getArrayFiveParameterizedTest, CheckGetArrayFive)
{
    FiveDigitArray fiveDigitArray_(std::get<0>(GetParam()));
    std::string expected_array = std::get<1>(GetParam());
    std::string result = fiveDigitArray_.get_array();
    ASSERT_EQ(expected_array, result);
}

INSTANTIATE_TEST_CASE_P(
    getArrayFiveTests,
    getArrayFiveParameterizedTest,
    ::testing::Values(
        std::make_tuple("1431242413", "1431242413"),
        std::make_tuple("0", "0"),
        std::make_tuple("123", "123")));

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}