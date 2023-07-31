#include "procstat.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CHUNK_SIZE 256UL

pstat_ret_t read_procstat(char** outbuf) { 
    FILE* procstat = fopen("/proc/stat", "r");

    if (procstat == NULL)
        return FAILED;

    fflush(procstat);
 
    char chunk_buf[CHUNK_SIZE];
    size_t length = 0;

    while(!feof(procstat)) {
        size_t bytes_read = fread(chunk_buf, 1UL, CHUNK_SIZE, procstat);

        if(bytes_read == 0)
            continue;

        length += bytes_read;

        if(ferror(procstat)) {
            fclose(procstat);
            return FAILED;
        }
      
        *outbuf = realloc(*outbuf, length);
        
        memcpy(*outbuf + (length - bytes_read), (const char*)chunk_buf, bytes_read); 
    }

    *outbuf = realloc(*outbuf, length + 1);
    memset(*outbuf + length, 0, 1UL); // null terminate the string
    
    fclose(procstat);

    return SUCCESS;
}
