SET(http_src http/client.cpp http/server.cpp)
SET(http_srcs ${http_src} PARENT_SCOPE)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/cpp-httplib)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)

add_library(paio_http ${http_src})
target_link_libraries(paio_http Threads::Threads)


