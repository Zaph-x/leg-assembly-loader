add_library(doctest OBJECT doctest.cpp)

add_executable(convert_test convert_test.cpp ../src/converter/converter.cpp)
target_link_libraries(convert_test PRIVATE doctest)

add_test(NAME convert_test COMMAND convert_test)