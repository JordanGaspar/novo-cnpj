add_executable(Debugging main.cpp)
target_link_libraries(Debugging PRIVATE CNPJ)

add_test(NAME DebuggingTest COMMAND test/Debugging)