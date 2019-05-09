set(simple_src simple.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(simple_ex ${simple_src})
target_link_libraries(simple_ex ${PAIO_LIBRARIES})
