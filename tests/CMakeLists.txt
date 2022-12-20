add_library(doctest OBJECT doctest.cpp)
file(COPY test_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(convert_test convert_test.cpp ../src/converter/converter.cpp)
add_executable(lexer_test lexer_test.cpp ../src/lexer.cpp)
add_executable(parser_test parser_test.cpp ../src/parser.cpp ../src/lexer.cpp ../include/parser.hpp ../src/converter/converter.cpp)
target_link_libraries(convert_test PRIVATE doctest)
target_link_libraries(lexer_test PRIVATE doctest)
target_link_libraries(parser_test PRIVATE doctest)


add_test(NAME convert_test COMMAND convert_test)
add_test(NAME lexer_test COMMAND lexer_test)
add_test(NAME parser_test COMMAND parser_test)
