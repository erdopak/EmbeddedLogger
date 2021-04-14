/**
 * !! WARNING !!
 * ! DO NOT INCLUDE THIS FILE !
 * Since this file contains data;
 * inclusion only valid for logger.c and logReader.c
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "log.h"

/**
 * @brief
 * MAX_LOG_COUNT defines entire system log buffer size
 */
#define MAX_LOG_COUNT 5000

/**
 * @brief
 * PARAM_DATA_BUFFER_SIZE defines parameter buffer size for logs of bytes
 */
#define DATA_BUFFER_SIZE 10000

/**
 * @brief
 * IS_RING_BUFFER determines whether logs will be overwritten from start point if max count 
 * of logs exceeds
 * set 0 this this if you don't want to lose initialization or starting logs 
 */
#define IS_RING_BUFFER 1

/**
 * @brief 
 * LOG_RECORD is an entry of a log with it's potential data parameter pointer
 */
typedef struct LOG_RECORD
{
    LOG_LEVEL level;
    LOG_CODE code;
    TIME_STAMP time;
    int dataPointer;
    int dataSize;
}LOG_RECORD;

/**
 * @brief 
 * The same copy of log array will be stored at both logger and log reader.
 */
LOG_RECORD logArray[MAX_LOG_COUNT];

/**
 * @brief
 * Data buffer will store parameters of the logs on the buffer.
 */
unsigned char dataBuffer[DATA_BUFFER_SIZE];

#endif //CONFIG_H