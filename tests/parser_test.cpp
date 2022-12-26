#include <filesystem>
#include "doctest.h"
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
        std::cout << parser.get_program()->get_architecture() << std::endl;
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




    /*SUBCASE("Par"){
        std::fstream file;
        const std::string path = "./test_files/function.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        file.open(path);
        std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        std::stringstream ss(ir);

        ARM::Lexer::Lexer lexer(ss);
        lexer.run();
        ARM::Parser::Parser parser;
        parser.set_up(lexer);

        parser.assign_program();
        CHECK(parser.get_program()->get_file_name() == "\"function.c\"");
    }*/
}