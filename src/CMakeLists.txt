add_library(parser SHARED parser.cpp lexer.cpp)

target_include_directories(parser PUBLIC ${PROJECT_SOURCE_DIR}/include)

INSTALL (TARGETS parser)