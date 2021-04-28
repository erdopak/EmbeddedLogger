#include <gtest/gtest.h>

extern "C"
{
    #include "log.h"
}

TEST(TEST_SUITE, WriteSuccesLogTest)
{
    LOG_STATUS status = LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, WriteFailLogTest)
{
    LOG_STATUS status = LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 801);
    EXPECT_EQ(status, LOG_WRITE_DATA_FAILED);
}