

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include/catch2)

add_executable(www_test www_test.cpp)
target_link_libraries(www_test  paio_http Catch2::Catch2)

add_test(NAME www_test COMMAND $<TARGET_FILE:www_test>) 
