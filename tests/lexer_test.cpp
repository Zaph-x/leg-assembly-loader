#include "doctest.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "lexer.hpp"

TEST_CASE("Lexer can generate register lexems") {
    SUBCASE("token is a W register") {
        std::string line("w0");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_curr_lexem().get_token() == ARM::Tokens::Token::W0);
    }
}
TEST_CASE("Lexer can generate datatype lexems") {
    SUBCASE("token is a string") {
        std::string line("\"Hello world\"");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_curr_lexem().get_token() == ARM::Tokens::Token::RAW_STRING);
    }
    SUBCASE("token is a hex number") {
        std::string line("0x1234");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_curr_lexem().get_token() == ARM::Tokens::Token::HEX_NUMBER);
    }
    SUBCASE("token is a decimal number") {
        std::string line("1234");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_curr_lexem().get_token() == ARM::Tokens::Token::DEC_NUMBER);
    }
}
TEST_CASE("Lexer can read large strings and generate lexems") {
    SUBCASE("Can read fully qualified arch directive with file name") {
        std::string line(R"(.arch armv8-a
.file "test.s")");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.run();
        CHECK(lexer.get_lexems()[0].get_token() == ARM::Tokens::Token::ARCHITECTURE);
        CHECK(lexer.get_lexems()[1].get_token() == ARM::Tokens::Token::ARMV8_A);
        CHECK(lexer.get_lexems()[2].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[3].get_token() == ARM::Tokens::Token::FILE);
        CHECK(lexer.get_lexems()[4].get_token() == ARM::Tokens::Token::RAW_STRING);
        CHECK(lexer.get_lexems()[5].get_token() == ARM::Tokens::Token::EOF_TOKEN);
    }
    SUBCASE("Can read fully qualified arch directive with file name and retain values") {
        std::string line(R"(.arch armv8-a
.file "test.s")");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.run();
        CHECK(lexer.get_lexems()[0].get_curr_lexem().compare(".arch") == 0);
        CHECK(lexer.get_lexems()[1].get_curr_lexem().compare("armv8-a") == 0);
        CHECK(lexer.get_lexems()[2].get_curr_lexem().compare("\n") == 0);
        CHECK(lexer.get_lexems()[3].get_curr_lexem().compare(".file") == 0);
        CHECK(lexer.get_lexems()[4].get_curr_lexem().compare("\"test.s\"") == 0);
        CHECK(lexer.get_lexems()[5].get_curr_lexem().compare("") == 0);
    }
}

TEST_CASE("Lexer can read files and generate lexems") {
    SUBCASE("Can read file and lex it") {
        // Read a file into a stringstream and lex it
        std::fstream file;
        const std::string path = "./partial.s";

        file.open(path);
        std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        std::stringstream ss(ir);
        
        ARM::Lexer::Lexer lexer(ss);

        lexer.run();
        
        CHECK(lexer.get_lexems().size() > 0);
        CHECK(lexer.get_lexems()[0].get_token() == ARM::Tokens::Token::ARCHITECTURE);
        CHECK(lexer.get_lexems()[1].get_token() == ARM::Tokens::Token::ARMV8_A);
        CHECK(lexer.get_lexems()[2].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[3].get_token() == ARM::Tokens::Token::FILE);
        CHECK(lexer.get_lexems()[4].get_token() == ARM::Tokens::Token::RAW_STRING);
        CHECK(lexer.get_lexems()[5].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[6].get_token() == ARM::Tokens::Token::TEXT);
        CHECK(lexer.get_lexems()[7].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[8].get_token() == ARM::Tokens::Token::GLOBAL);
        CHECK(lexer.get_lexems()[9].get_token() == ARM::Tokens::Token::LABEL);
        CHECK(lexer.get_lexems()[10].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[11].get_token() == ARM::Tokens::Token::DATA_SECTION);
        CHECK(lexer.get_lexems()[12].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[13].get_token() == ARM::Tokens::Token::ALIGN);
        CHECK(lexer.get_lexems()[14].get_token() == ARM::Tokens::Token::DEC_NUMBER);
        CHECK(lexer.get_lexems()[15].get_token() == ARM::Tokens::Token::EOL_TOKEN);
        CHECK(lexer.get_lexems()[16].get_token() == ARM::Tokens::Token::TYPE);
        CHECK(lexer.get_lexems()[17].get_token() == ARM::Tokens::Token::LABEL);

    }
}