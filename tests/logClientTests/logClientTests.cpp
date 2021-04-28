#include <gtest/gtest.h>

extern "C"
{
    #include "logClient.h"
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

TEST(TEST_SUITE, LogFlushTest)
{
    LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 801);
    unsigned char* logBuffer = transferLogs();
    int logCount = *(int*)logBuffer;
    EXPECT_NE(logCount, 0);
    flushLogs();
    logCount = *(int*)logBuffer;
    EXPECT_EQ(logCount, 0);
}
