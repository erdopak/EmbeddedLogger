#ifndef LOG_CLIENT_H
#define LOG_CLIENT_H

#include "log.h"

/**
 * @brief 
 * This function add logs to the buffer as bulk.
 * Logs are seperated with ['#', '#'] as caution
 * Bulk of logs terminated with ['#', '#', '#', '#'] 
 * @param level: level of the log
 * @param code: message of the log
 * @param time: time stamp of the log
 * @param data: any data parameters come with the log
 * @param dataSize: size of the custom data
 */
void addLog(LOG_LEVEL level, LOG_CODE code, TIME_STAMP time, void* data, int dataSize);

/**
 * @brief 
 * Returns log buffer to transfer, resets the data pointer
 * @return unsigned char* logBuffer
 */
unsigned char* transferLogs();

#endif // LOG_CLIENT_H
