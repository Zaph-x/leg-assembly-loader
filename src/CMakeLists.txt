add_compile_options(-Wall -Wextra -Wpedantic)

add_library(parser SHARED parser.cpp lexer.cpp ../include/vector_stream.hpp)

target_include_directories(parser PUBLIC ${PROJECT_SOURCE_DIR}/include)

INSTALL (TARGETS parser)
