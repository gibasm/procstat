
set(TEST_SOURCES
${SRC_ROOT_DIR}/reader/procstat.c
${SRC_ROOT_DIR}/fifo/queue.c
"tests.c")

add_executable(test ${TEST_SOURCES})
