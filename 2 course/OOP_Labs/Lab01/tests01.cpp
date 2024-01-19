#include <gtest/gtest.h>
#include "ValueAndSolveTask.h"

class CorrectLineParameterizedTestFixture :public ::testing::TestWithParam<std::string> {
protected:
    std::string line;
};

TEST_P(CorrectLineParameterizedTestFixture, CheckIsCorrectLines) {
    std::string line = GetParam();
    bool result=isCorrectLine(line);
    ASSERT_EQ(true,result);
}

INSTANTIATE_TEST_CASE_P(
        CorrectLineTests,
        CorrectLineParameterizedTestFixture,
        ::testing::Values(
                "abc", "ccc", "aaa", "b"
        ));

TEST(test_check_func_swapAtoBorBtoA,test_check_for_ordinary_input)
{
    std::string line="acb";
    std::string result=swapAtoBorBtoA(line);
    ASSERT_EQ("bca",result);
}

TEST(test_check_func_swapAtoBorBtoA,test_check_for_only_c)
{
    std::string line="ccc";
    std::string result=swapAtoBorBtoA(line);
    ASSERT_EQ("ccc",result);
}

TEST(test_check_func_swapAtoBorBtoA,test_check_for_only_a)
{
    std::string line="a";
    std::string result=swapAtoBorBtoA(line);
    ASSERT_EQ("b",result);
}

TEST(test_check_func_swapAtoBorBtoA,test_check_for_only_b)
{
    std::string line="bbb";
    std::string result=swapAtoBorBtoA(line);
    ASSERT_EQ("aaa",result);
}


TEST(test_check_func_swapAtoBorBtoA,test_check_for_only_ab)
{
    std::string line="baba";
    std::string result=swapAtoBorBtoA(line);
    ASSERT_EQ("abab",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_number)
{
    std::string line="abc7";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_another_symbol_brackets)
{
    std::string line="abbb{cccaa}";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_another_symbol_cobachka)
{
    std::string line="aa@a";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_only_another_symbol)
{
    std::string line="%";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_another_alphabet)
{
    std::string line="aа";// вторая а c русской раскладки
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_upper_letter)
{
    std::string line="AABBC";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_check_for_space)
{
    std::string line="cac cbc";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("Received another symbol!!!",result);
}

TEST(test_check_func_trySwapAtoBorBtoA,test_correct_line)
{
    std::string line="abbabcbbccccca";
    std::string result=trySwapAtoBorBtoA(line);
    ASSERT_EQ("baabacaacccccb",result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}