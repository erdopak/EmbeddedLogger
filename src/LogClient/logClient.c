#include <string.h>
#include "logClient.h"

#define LOCAL_BUFFER_SIZE       800     //In bytes
#define MID_TERMINATOR_SIZE     2       //In bytes
#define LAST_TERMINATOR_SIZE    4       //In bytes

unsigned char dataBuffer[LOCAL_BUFFER_SIZE];
static unsigned int dataPointer = 0;
static char terminator[] = { '#', '#', '#', '#'};
const static int levelSize = sizeof(LOG_LEVEL);
const static int logCodeSize = sizeof(LOG_CODE);
const static int timeStampSize = sizeof(TIME_STAMP);
const static int logHeaderSize = sizeof(LOG_LEVEL) + sizeof(LOG_CODE) 
                                        + sizeof(TIME_STAMP) + LAST_TERMINATOR_SIZE;

void addLog(LOG_LEVEL level, LOG_CODE code, TIME_STAMP time, void* data, int dataSize)
{
    if(dataPointer + (logHeaderSize + dataSize) < LOCAL_BUFFER_SIZE)
    {
        // The previous log was last one but it will be trimmed by MID_TERMINATOR_SIZE
        // now new log became last
        if(dataPointer >= MID_TERMINATOR_SIZE)
        {
            dataPointer -= MID_TERMINATOR_SIZE;
        }

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

        //copy log terminator
        memcpy(&dataBuffer[dataPointer], terminator, LAST_TERMINATOR_SIZE);
        dataPointer += LAST_TERMINATOR_SIZE;
    }
}

unsigned char* transferLogs()
{
    dataPointer = 0;
    return dataBuffer; 
} 
