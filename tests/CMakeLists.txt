add_library(doctest OBJECT doctest.cpp)
file(COPY test_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(convert_test convert_test.cpp ../src/converter/converter.cpp)
add_executable(lexer_test lexer_test.cpp ../src/lexer.cpp)
target_link_libraries(convert_test PRIVATE doctest)
target_link_libraries(lexer_test PRIVATE doctest)


add_test(NAME convert_test COMMAND convert_test)
add_test(NAME lexer_test COMMAND lexer_test)
