

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Catch2/CMake")
#find_package(Catch2 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include/catch2)

add_executable(www_test www_test.cpp)
target_link_libraries(www_test Catch2::Catch2)

add_test(NAME www_test COMMAND $<TARGET_FILE:www_test>) 
