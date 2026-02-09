add_executable(Debugging1 test1.cpp)
target_link_libraries(Debugging1 PUBLIC ${PROJECT_NAME})
add_test(NAME DebuggingTest1 COMMAND test/Debugging1)

add_executable(Debugging2 test2.cpp)
target_link_libraries(Debugging2 PUBLIC ${PROJECT_NAME} Rest)
add_test(NAME DebuggingTest2 COMMAND test/Debugging2)