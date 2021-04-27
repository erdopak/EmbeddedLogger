#include <gtest/gtest.h>

extern "C"
{
    #include "log.h"
}

TEST(TEST_SUITE, WriteSuccesLogTest)
{
    EXPECT_EQ(1, 1);
}