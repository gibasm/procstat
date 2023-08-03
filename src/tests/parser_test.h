#include <assert.h>
#include "parser.h"

const char* valid_pstat_string =
"cpu  135711 16 31369 3914281 97394 13892 4630 0 0 0\n"
"cpu0 16343 1 3460 493693 9590 824 587 0 0 0\n"
"cpu1 14588 0 3742 492783 5339 6499 452 0 0 0\n"
"cpu2 18537 0 3992 488531 9735 2797 346 0 0 0\n"
"cpu3 15632 0 3720 482186 22190 719 381 0 0 0\n"
"cpu4 18038 0 4035 484024 16753 1031 354 0 0 0\n"
"cpu5 13698 0 5377 494299 10605 628 2054 0 0 0\n"
"cpu6 20109 3 3924 486215 13166 862 281 0 0 0\n"
"cpu7 18762 8 3116 492547 10012 530 172 0 0 0\n"
"ctxt 17361859\n"
"btime 1691003122\n"
"processes 13212\n"
"procs_running 1\n"
"procs_blocked 0\n"
"softirq 4007546 298 473929 14 93947 72524 0 53922 1879701 12 1433199\n"
;

const char* invalid_pstat_string =
"123123 123123 123123\n"
"cpu 123 123 123 \n";

void parser_should_successfully_parse_a_valid_string() {
    pstat_cpu_times_t pstat_cpu_times;

    assert(parse_pstat_string(valid_pstat_string, &pstat_cpu_times) == PARSER_SUCCESS);
    cpu_times_free(&pstat_cpu_times);
}

void parser_should_fail_when_parsing_an_invalid_string() {
    pstat_cpu_times_t pstat_cpu_times;

    assert(parse_pstat_string(invalid_pstat_string, &pstat_cpu_times) == PARSER_FAILED);
    cpu_times_free(&pstat_cpu_times);
}
