
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include/catch2)

add_executable(www_test www_test.cpp)
target_link_libraries(www_test  paio_http Catch2::Catch2)
add_test(NAME www_test COMMAND $<TARGET_FILE:www_test>) 


add_executable(json_test json_test.cpp)
target_link_libraries(json_test  paio_datatype Catch2::Catch2)
add_test(NAME json_test COMMAND $<TARGET_FILE:json_test>) 

add_executable(broker_test broker_test.cpp)
target_link_libraries(broker_test  paio_broker Catch2::Catch2)
add_test(NAME broker_test COMMAND $<TARGET_FILE:broker_test>) 
