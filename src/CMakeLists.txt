set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SRC_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/reader/)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/)

