#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EXPECTED_MIN_NTIMES 10UL

#define SKIP_WHITESPACES(ptr) while(*ptr == ' ') ++ptr
#define SKIP_WHITESPACES_AND_NEWLINES(ptr) while((*ptr == ' ') || (*ptr == '\n')) ++ptr

parser_ret_t parse_pstat_string(const char* pstat_str, pstat_cpu_times_t* pstat_cpu_times) {
    pstat_cpu_times->n_cpus = 0UL;
    pstat_cpu_times->n_times = 0UL;

    char* begin = (char*)pstat_str;

    if(strncmp((const char*)begin, "cpu", 3UL) != 0)
        return PARSER_FAILED;
  
    begin += 3UL;

    if(*begin != ' ')
        return PARSER_FAILED;
    
    pstat_cpu_times->n_cpus = 1UL;

    pstat_cpu_times->cpu_times = (uint64_t**)malloc(sizeof(uint64_t*));
    pstat_cpu_times->cpu_times[0] = (uint64_t*)calloc(EXPECTED_MIN_NTIMES, sizeof(uint64_t));
   
    size_t time_pos = 0;
    while(*begin != '\n') {
        int read_chars;

        SKIP_WHITESPACES(begin);

        if(pstat_cpu_times->n_times > EXPECTED_MIN_NTIMES) 
            pstat_cpu_times->cpu_times[0] = (uint64_t*)realloc(pstat_cpu_times->cpu_times[0], pstat_cpu_times->n_times); 

        uint64_t time;
        if(sscanf((const char*)begin, "%lu%n", &time, &read_chars) != 1) {
            return PARSER_FAILED;
        }

        pstat_cpu_times->cpu_times[0][time_pos] = time;
        ++time_pos;

        pstat_cpu_times->n_times += 1;    
        begin += read_chars;
    }

    if(pstat_cpu_times->n_times < EXPECTED_MIN_NTIMES) 
        pstat_cpu_times->cpu_times[0] = (uint64_t*)realloc(pstat_cpu_times->cpu_times[0], pstat_cpu_times->n_times); 

    while(*begin != '\0') {
        SKIP_WHITESPACES_AND_NEWLINES(begin);

        int read_chars;
        size_t ncpu;
        if(sscanf((const char*)begin, "cpu%zu%n", &ncpu, &read_chars) != 1) {
            break;
        }
        
        begin += read_chars;

        if((ncpu+1) != pstat_cpu_times->n_cpus)
            return PARSER_FAILED;
        
        pstat_cpu_times->cpu_times = (uint64_t**)realloc(pstat_cpu_times->cpu_times, (ncpu + 2UL) * sizeof(uint64_t*));

        pstat_cpu_times->cpu_times[ncpu + 1] = (uint64_t*)calloc(pstat_cpu_times->n_times, sizeof(uint64_t));
        
        for(time_pos = 0; time_pos < pstat_cpu_times->n_times; ++time_pos) {
            SKIP_WHITESPACES(begin); 

            uint64_t time;

            if(sscanf((const char*)begin, "%lu%n", &time, &read_chars) != 1) {
                return PARSER_FAILED;
            }
            
            pstat_cpu_times->cpu_times[ncpu + 1][time_pos] = time;
            begin += read_chars;
        }
        
        pstat_cpu_times->n_cpus += 1;
    }

    return PARSER_SUCCESS;
}

void cpu_times_free(pstat_cpu_times_t* pstat_cpu_times) {
    for(size_t i = 0; i < pstat_cpu_times->n_cpus; ++i)
        free(pstat_cpu_times->cpu_times[i]);
    
    if(pstat_cpu_times->n_cpus != 0)
        free(pstat_cpu_times->cpu_times);
}
