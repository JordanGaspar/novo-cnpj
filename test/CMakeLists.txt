add_executable(Debugging main.cpp)
target_link_libraries(Debugging PUBLIC ${PROJECT_NAME})

add_test(NAME DebuggingTest COMMAND test/Debugging)