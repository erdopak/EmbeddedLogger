#ifndef LOG_H
#define LOG_H

typedef unsigned long TIME_STAMP;

/**
 * @brief  
 * Severity levels of the logs 
 */
typedef enum LOG_LEVEL
{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    CRITICAL = 5
}LOG_LEVEL;

/**
 * @brief 
 * Enumeration values of corresponding strings
 * This enum helps to keep memory fixed instead of undeterministic strings
 * 
 * Define your log message here it will be converted string when logs dumped
 */
typedef enum LOG_CODE
{
    EXAMPLE_LOG = 0
}LOG_CODE;

/**
 * @brief
 * LOG_STATUS enum defines the log write return value of LOG function
 * This enumeration is important especially when you use ring buffer 
 * or large chunks of parameter data.
 */
typedef enum LOG_STATUS
{
    LOG_WRITE_FAILED = 0,
    LOG_WRITE_SUCCESS = 1,
    LOG_WRITE_DATA_FAILED = 2,
    LOG_OVERWRITTEN = 3
}LOG_STATUS;

/**
 * @brief 
 * LOG function stores the momentarily states.
 * Function name specifically left upper case to comply on log standards
 * @param level: Priority of the log
 * @param code: Log message enumeration
 * @param time: epoch time
 * @param data: data pointer to params to be copied
 * @param dataSize: size of the data to be copied
 */
LOG_STATUS LOG(LOG_LEVEL level, LOG_CODE code, TIME_STAMP time, void* data, int dataSize);

/**
 * @brief
 * flushLogs deletes all the data from log record array
 * does not touch to the param data array since it's controlled by log record array
 */
void flushLogs();

#endif //LOG_H
