set(http_src http/client.cpp http/server.cpp)
set(http_srcs ${http_src} PARENT_SCOPE)

set(datatype_src datatype/json.cpp)
set(datatype_srcs ${datatype_src} PARENT_SCOPE)

set(broker_src broker.cpp object_broker.cpp)
set(broker_srcs ${broker_src} PARENT_SCOPE)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/cpp-httplib)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/rapidjson/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)

add_library(paio_http ${http_src})
target_link_libraries(paio_http Threads::Threads)

set(paio_http_libs paio_http)

add_library(paio_datatype ${datatype_src})
target_link_libraries(paio_datatype Threads::Threads)

add_library(paio_broker ${broker_src})
target_link_libraries(paio_broker Threads::Threads ${paio_http_libs})


