#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "procstat.h"

void read_procstat_should_read_nonempty_string() {
    char* strbuf = NULL;

    pstat_ret_t result = read_procstat(&strbuf);

    assert(result == PSTAT_SUCCESS);
    assert(strlen((const char*)strbuf) != 0);

    free(strbuf);
}
