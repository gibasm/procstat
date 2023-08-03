
set(TEST_SOURCES
${SRC_ROOT_DIR}/reader/procstat.c
${SRC_ROOT_DIR}/fifo/queue.c
${SRC_ROOT_DIR}/analyzer/parser.c
${SRC_ROOT_DIR}/analyzer/calc_usage.c
"tests.c")

add_executable(test ${TEST_SOURCES})
