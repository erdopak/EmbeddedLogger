#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief 
 * memLocate frees as given dataSize from parameter buffer.
 * freeing operation starts from oldest log.
 * @param dataSize: specifies how much memory needed to store next data.
 */
void memLocate(int dataSize);

/**
 * @brief
 * writeMemory checks the boundaries of the data buffer and writes accordingly.
 * @param data: pointer to the data to copy.
 * @param dataSize: size of the data to be copied.
 */
int writeMemory(void* data, int dataSize);

/**
 * @brief 
 * Parses bulks of logs which come from log clients.
 */
void readBulkLogs(unsigned char* data);

#endif // LOGGER_H
