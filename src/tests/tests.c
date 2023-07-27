#include "procstat_test.h"
#include "queue_test.h"
#include <stdio.h>

int main(void)
{
    read_procstat_should_read_nonempty_string();    
    queue_push_should_return_success_when_nonfull();
    queue_pop_should_return_success_when_nonempty();
    queue_push_should_return_queue_full_when_full();
    queue_pop_should_return_queue_empty_when_empty();
    printf("--- All tests passed ---\n\r");
    return 0;
}

