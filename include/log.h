#ifndef LOG_H
#define LOG_H

typedef unsigned long TIME_STAMP;

typedef enum LOG_LEVEL
{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    CRITICAL = 5
}LOG_LEVEL;

/*
 * Define your log message here
 */
typedef enum LOG_CODE
{
    EXAMPLE_LOG = 0
}LOG_CODE;

typedef enum LOG_STATUS
{
    LOG_WRITE_FAILED = 0,
    LOG_WRITE_SUCCES = 1,
    LOG_WRITTEN_DATA_FAILED = 2,
    LOG_OVERWRITTEN = 3
}LOG_STATUS;

/*
 * LOG function stores the momentarily states.
 * @param level: Priority of the log
 * 
 */
LOG_STATUS LOG(LOG_LEVEL level, LOG_CODE code, TIME_STAMP time, void* data, int dataSize);

void flushLogs();

#endif //LOG_H
