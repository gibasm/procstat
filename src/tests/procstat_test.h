#include <assert.h>
#include <string.h>
#include "procstat.h"

#define STR_BUFSIZE 128UL

void read_procstat_should_read_nonempty_string() {
    char strbuf[STR_BUFSIZE];
    size_t size = STR_BUFSIZE;

    pstat_ret_t result = read_procstat(strbuf, size);

    assert(result == SUCCESS);
    assert(strlen((const char*)strbuf) != 0);
}
