#include <string.h>
#include "logClient.h"

/**
 * @brief 
 * Size of log buffer of bytes
 */
#define LOCAL_BUFFER_SIZE       800

/**
 * @brief 
 * First 4 bytes are reserved for log count.
 * Rest is heap style log buffer.
 */
unsigned char dataBuffer[LOCAL_BUFFER_SIZE] = {0};

/**
 * @brief 
 * Count of log this value will be copied to beginning of the databuffer just before transfering.
 */
static int logCounter = 0;

/**
 * @brief 
 * Pointer to the first free index of the data buffer
 */
static unsigned int dataPointer = sizeof(int);

/**
 * @brief 
 * Constant variables kept to avoid run time calculations
 */
const static int levelSize = sizeof(LOG_LEVEL);
const static int logCodeSize = sizeof(LOG_CODE);
const static int timeStampSize = sizeof(TIME_STAMP);
const static int logHeaderSize = sizeof(LOG_LEVEL) + sizeof(LOG_CODE) 
                                        + sizeof(TIME_STAMP);

LOG_STATUS LOG(LOG_LEVEL level, LOG_CODE code, TIME_STAMP time, void* data, int dataSize)
{
    if(dataPointer + (logHeaderSize + dataSize) < LOCAL_BUFFER_SIZE)
    {
        //copy the log level
        memcpy(&dataBuffer[dataPointer], &level, levelSize);
        dataPointer += levelSize;

        //copy the log code
        memcpy(&dataBuffer[dataPointer], &code, logCodeSize);
        dataPointer += logCodeSize;

        //copy the time stamp
        memcpy(&dataBuffer[dataPointer], &time, timeStampSize);
        dataPointer += timeStampSize;

        //copy the time stamp
        memcpy(&dataBuffer[dataPointer], &dataSize, sizeof(int));
        dataPointer += sizeof(int);
        
        //copy the parameters
        if(dataSize > 0)
        {
            memcpy(&dataBuffer[dataPointer], &data, dataSize);
            dataPointer += dataSize;
        }
        logCounter++;

        return LOG_WRITE_SUCCESS;
    }
    return LOG_WRITE_DATA_FAILED;
}

unsigned char* transferLogs()
{
    dataPointer = sizeof(int);
    *(int*)dataBuffer = logCounter;
    logCounter = 0;
    return dataBuffer; 
} 
