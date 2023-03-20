#include "gtest/gtest.h"

#include <vector>

#include "common/print.h"
#include "common/cal.h"


TEST(testPrint, test0)
{
    std::vector<int> arr = {1,2,3};
    std::cout << "arr:" << std::endl;
    std::cout << arr << std::endl;
}


TEST(testAdd, test0)
{
    EXPECT_EQ(add(4,6), 10);
    EXPECT_EQ(add(14,16), 30);
    EXPECT_EQ(add(-4,-6), -10);
}

TEST(testAdd, test1)
{
    EXPECT_EQ(add(4,0), 4);
    EXPECT_EQ(add(0,0), 0);
}

