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

    SUBCASE("Can parse the constants.s file successfully") {
        std::string path = "./test_files/constants.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();

        SUBCASE("Can parse the architecture") {
            CHECK(parser.get_program()->get_architecture() == "armv8-a");
        }
        SUBCASE("Can parse the file name") {
            CHECK(parser.get_program()->get_file_name() == "\"constants.c\"");
        }
        SUBCASE("Can assign some global variables") {
            CHECK(parser.get_program()->get_global_variables().size() > 0);
        }
        SUBCASE("Can get a variable from the program") {
            CHECK(parser.get_program()->get_variable("a") != nullptr);
        }
        SUBCASE("Can assign a global variable as reference to a string") {
            auto ref = parser.get_program()->get_variable("f");
            CHECK(ref->get_type() == ARM::Parser::GlobalType::REF);
            auto lc0 = parser.get_program()->get_variable(".LC0");
            CHECK(lc0->get_type() == ARM::Parser::GlobalType::O);
        }

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

/*    SUBCASE("Parser can parse a decently written program") {
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
*/
}
