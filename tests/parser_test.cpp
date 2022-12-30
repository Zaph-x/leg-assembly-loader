#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <filesystem>
#include "doctest/doctest.h"
#include "parser.hpp"



TEST_CASE("Parser can parse small programs") {
    SUBCASE("Empty program") {
        std::string path = "./test_files/empty_program.s";
        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();
        CHECK(parser.get_program()->get_architecture() == "");
        CHECK(parser.get_program()->get_file_name() == "");
    }

    SUBCASE("Can parse architecture") {
        std::string path = "./test_files/branch.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();

        CHECK(parser.get_program()->get_architecture() == "armv8-a");
    }


    SUBCASE("Can parse file name") {
        std::string path = "./test_files/branch.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();

        CHECK(parser.get_program()->get_file_name() == "\"branch.c\"");
    }

    SUBCASE("Can parse file name 2") {
        std::string path = "./test_files/madd.s";
        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();

        CHECK(parser.get_program()->get_file_name() == "\"madd.c\"");
    }

    SUBCASE("Parser can correctly assign amound of functions to a program"){
        const std::string path = "./test_files/function.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));


        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();
        CHECK(parser.get_program()->get_file_name() == "\"function.c\"");
        CHECK(parser.get_program()->get_architecture() == "armv8-a");
        CHECK(parser.get_program()->get_functions().size() == 9);
    }


    SUBCASE("Parser can correctly assign instructions to functions in a program"){
        const std::string path = "./test_files/function.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));


        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();
        CHECK(parser.get_program()->get_file_name() == "\"function.c\"");
        CHECK(parser.get_program()->get_architecture() == "armv8-a");
        CHECK(parser.get_program()->get_function("main")->get_instructions().size() == 21);
    }

    SUBCASE("Parser can parse a decently written program") {
        const std::string path = "./test_files/imperial_distance.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();
        CHECK(parser.get_program()->get_file_name() == "\"imperial_distance.c\"");
        CHECK(parser.get_program()->get_architecture() == "armv8-a");
        CHECK(parser.get_program()->get_functions().size() == 1);
        CHECK(parser.get_program()->get_function("main")->get_instructions().size() == 106);
    }
}
