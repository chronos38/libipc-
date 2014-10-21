#include "gtest/gtest.h"
#include <vector>
#include <algorithm>

TEST(test1, sort_test)
{
    std::vector<int> test = {1, 50, 6, 2, 10, 32};
    std::vector<int> expect = {1, 2, 6, 10, 32, 50};

    std::sort(test.begin(), test.end());

    for(int i; i < test.size(); i++) {
        EXPECT_EQ(test[i], expect[i]);
    }
}
