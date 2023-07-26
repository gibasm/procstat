#include "procstat.h"
#include <stdio.h>

pstat_ret_t read_procstat(char* outbuf, size_t size) { 
    FILE* procstat = fopen("/proc/stat", "r");

    if (procstat == NULL || outbuf == NULL)
        return FAILED;

    fflush(procstat);
 
    char* read_ptr = outbuf;
    /* reserve one byte for NULL byte at the end of a string */
    size_t bytes_to_read = size - 1; 
    pstat_ret_t retval = SUCCESS; 

    while(!feof(procstat) && (bytes_to_read != 0)) {
        size_t bytes_read = fread(read_ptr, 1UL, bytes_to_read, procstat);

        if(ferror(procstat)) {
            retval = FAILED;
            break;
        }

        read_ptr += bytes_read;
        bytes_to_read -= bytes_read;
    }

    *read_ptr = '\0';

    fclose(procstat);

    return retval;
}
