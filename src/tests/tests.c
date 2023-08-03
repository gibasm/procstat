#include "procstat_test.h"
#include "queue_test.h"
#include "parser_test.h"
#include "calc_usage_test.h"
#include <stdio.h>

int main(void)
{
    read_procstat_should_read_nonempty_string();    
    queue_push_should_return_success_when_nonfull();
    queue_pop_should_return_success_when_nonempty();
    queue_push_should_return_queue_full_when_full();
    queue_pop_should_return_queue_empty_when_empty();
    parser_should_successfully_parse_a_valid_string();
    parser_should_fail_when_parsing_an_invalid_string();
    calc_cpu_usage_should_return_100_percent_for_full_utilization();
    calc_cpu_usage_should_return_25_percent_for_quarter_utilization();
    printf("--- All tests passed ---\n\r");
    return 0;
}

