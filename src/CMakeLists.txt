set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SRC_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/reader/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/analyzer/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/printer/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/fifo/)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/)

set(SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/reader/procstat.c
${CMAKE_CURRENT_SOURCE_DIR}/reader/reader.c
${CMAKE_CURRENT_SOURCE_DIR}/fifo/queue.c
${CMAKE_CURRENT_SOURCE_DIR}/analyzer/parser.c
${CMAKE_CURRENT_SOURCE_DIR}/analyzer/calc_usage.c
${CMAKE_CURRENT_SOURCE_DIR}/analyzer/analyzer.c
${CMAKE_CURRENT_SOURCE_DIR}/printer/printer.c
${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

add_executable(pstat ${SOURCES})
