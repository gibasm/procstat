#include "procstat_test.h"
#include <stdio.h>

int main(void)
{
    read_procstat_should_read_nonempty_string();    
    printf("--- All tests passed ---\n\r");
    return 0;
}

