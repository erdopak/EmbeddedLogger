#include <string.h>
#include "config.h"
#include "logger.h"

/**
 * @brief 
 * Current index of the parameter buffer 
 */
static unsigned int dataPointer = 0;

/**
 * @brief 
 * Holds the latest index of the log entry array 
 */
static unsigned int logCounter = 0;

/**
 * @brief 
 * Datapointer should know counter is restarted so it can overwrite.
 */
static unsigned int isRestarted = 0; 

/**
 * @brief 
 * In case of logCounter restarted, safe pointer holds the latest previous data pointer 
 * log serie to avoid collision
 */
static unsigned int safePointer =  DATA_BUFFER_SIZE;

LOG_STATUS LOG(LOG_LEVEL level, LOG_CODE code, TIME_STAMP time, void* data, int dataSize)
{
    LOG_STATUS retVal = LOG_WRITE_FAILED;

    if(logCounter < MAX_LOG_COUNT)
    {
        logArray[logCounter].level = level;
        logArray[logCounter].time = time;
        logArray[logCounter].dataPointer = writeMemory(data, dataSize);
        logArray[logCounter].dataSize = dataSize;
        if(logArray[logCounter].dataPointer == -1)
        {
            retVal = LOG_WRITE_DATA_FAILED;
        }
        else
        {
            retVal = LOG_WRITE_SUCCESS;
        }
        logCounter++;
    }
    else if (IS_RING_BUFFER)
    {
        safePointer = logArray[logCounter-1].dataPointer;
        isRestarted = 1;
        logCounter = 0;
        retVal = LOG_OVERWRITTEN;
    }

    return retVal;
}

void memLocate(int dataSize)
{
    int currentCounter = logCounter;
    int cumulativeSize = 0;
    if(logArray[currentCounter].dataSize < dataSize)
    {
        cumulativeSize = logArray[currentCounter].dataSize;
        currentCounter++;
        while(currentCounter < MAX_LOG_COUNT)
        {
            //allocated area is not enough for current data, delete oldest one till it's enough
            if(logArray[currentCounter].dataSize + cumulativeSize <  dataSize)
            {
                //cumulate and overwrite previous
                cumulativeSize += logArray[currentCounter].dataSize;

                //overwrite data
                logArray[currentCounter].dataPointer = -1;
                logArray[currentCounter].dataSize = -1;
                currentCounter++;
            }
            else
            {
                break;
            }
        }
    }

}

int writeMemory(void* data, int dataSize)
{
    int retAddress = 0;
    if(dataPointer + dataSize < DATA_BUFFER_SIZE &&
        dataPointer + dataSize < safePointer)
    {
        memcpy(&dataBuffer[dataPointer], data, dataSize);
        dataPointer += dataSize;
        retAddress = dataPointer;
    }
    else if(isRestarted)
    {
        if(dataSize < safePointer)
        {
            memLocate(dataSize);
            memcpy(&dataBuffer[dataPointer], data, dataSize);

            //data pointer restart
            dataPointer = dataSize;
            retAddress = dataPointer;
        }
        else
        {
            retAddress = -1;
        }
        
    }
    else
    {
        //memory is not sufficient
        retAddress = -1;
    }

    return retAddress;
}

void readBulkLogs(unsigned char* data)
{
    int logCounter = *(int*)data;
    int bufferPointer = sizeof(int);
    void *logLevel, *logCode, *timeStamp, *dataSize;

    for(int i = 0; i < logCounter; i++)
    {
        logLevel = &data[bufferPointer];
        bufferPointer += sizeof(LOG_LEVEL);
        logCode = &data[bufferPointer];
        bufferPointer += sizeof(LOG_CODE);
        timeStamp = &data[bufferPointer];
        bufferPointer += sizeof(LOG_CODE);
        dataSize = &data[bufferPointer];
        bufferPointer += sizeof(int);
        
        LOG(
            *(LOG_LEVEL*)logLevel,
            *(LOG_CODE*)logCode,
            *(TIME_STAMP*)timeStamp,
            &data[bufferPointer],
            *(int*)dataSize
        );

        bufferPointer += *(int*)dataSize;
    }
}

void flushLogs()
{
    logCounter = 0;
    memset(logArray, 0, sizeof(LOG_RECORD) * MAX_LOG_COUNT);
}
