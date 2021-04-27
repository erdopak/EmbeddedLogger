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

TEST(TEST_SUITE, TraceLogTest)
{
    LOG_STATUS status = LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, DebugLogTest)
{
    LOG_STATUS status = LOG(DEBUG, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, InfoLogTest)
{
    LOG_STATUS status = LOG(INFO, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, WarnLogTest)
{
    LOG_STATUS status = LOG(WARN, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, ErrorLogTest)
{
    LOG_STATUS status = LOG(ERROR, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, CriticalLogTest)
{
    LOG_STATUS status = LOG(CRITICAL, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 0);
    EXPECT_EQ(status, LOG_WRITE_SUCCESS);
}

TEST(TEST_SUITE, WriteFailLogTest)
{
    LOG_STATUS status = LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, NULL, 10001);
    EXPECT_EQ(status, LOG_WRITE_DATA_FAILED);
}

TEST(TEST_SUITE, OverwrittenLogTest)
{
    flushLogs();
    int i;
    for (i = 0; i < 1000; i++)
    {
        LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, &i, sizeof(int));
    }
    LOG_STATUS status = LOG(TRACE, EXAMPLE_LOG, (TIME_STAMP)0, &i, sizeof(int));
    EXPECT_EQ(status, LOG_OVERWRITTEN);
}