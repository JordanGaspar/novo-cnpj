add_executable(Debuging main.cpp)
target_link_libraries(Debuging PRIVATE ${PROJECT_NAME})
set_target_properties(Debuging PROPERTIES CXX_STANDARD 23)

add_test(Debuging ${CMAKE_CURRENT_BINARY_DIR}/test/Debuging)