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
        SUBCASE("Can assign name of file to program") {
            CHECK(parser.get_program()->get_file_name() == "\"function.c\"");
        }
        SUBCASE("Can assign architecture to program") {
            CHECK(parser.get_program()->get_architecture() == "armv8-a");
        }
        SUBCASE("Can assign functions to program") {
            CHECK(parser.get_program()->get_functions().size() == 9);
        }
        SUBCASE("Can assign correct amount of instructions to main function") {
            CHECK(parser.get_program()->get_function("main")->get_instructions().size() == 21);
            SUBCASE("Correctly assigned first and final instruction of main function") {
                CHECK(parser.get_program()->get_function("main")->get_instructions()[0]->get_name() == ".cfi_startproc");
                CHECK(parser.get_program()->get_function("main")->get_instructions()[20]->get_name() == ".cfi_endproc");
            }
            SUBCASE("Correctly assigns arguments to a MOV instruction") {
                CHECK(parser.get_program()->get_function("main")->get_instructions()[5]->get_args().size() == 2);
                CHECK(std::dynamic_pointer_cast<ARM::Parser::Register>(parser.get_program()->get_function("main")->get_instructions()[5]->get_args()[0]) != nullptr);
                CHECK(std::dynamic_pointer_cast<ARM::Parser::Register>(parser.get_program()->get_function("main")->get_instructions()[5]->get_args()[0])->get_name() == "x29");
                CHECK(std::dynamic_pointer_cast<ARM::Parser::Register>(parser.get_program()->get_function("main")->get_instructions()[5]->get_args()[1]) != nullptr);
                CHECK(std::dynamic_pointer_cast<ARM::Parser::ImmediateValue>(parser.get_program()->get_function("main")->get_instructions()[5]->get_args()[1]) == nullptr);
                CHECK(std::dynamic_pointer_cast<ARM::Parser::Register>(parser.get_program()->get_function("main")->get_instructions()[5]->get_args()[1])->get_name() == "sp");
            }
        }
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
