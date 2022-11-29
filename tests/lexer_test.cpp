#include "doctest.h"
#include <string>
#include "lexer.hpp"

TEST_CASE("Lexer can generate register lexems") {
    SUBCASE("token is a W register") {
        std::string line("w0");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_lexem().get_token() == ARM::Tokens::Token::W0);
    }
}
TEST_CASE("Lexer can generate datatype lexems") {
    SUBCASE("token is a string") {
        std::string line("\"Hello world\"");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_lexem().get_token() == ARM::Tokens::Token::STRING);
    }
    SUBCASE("token is a hex number") {
        std::string line("0x1234");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_lexem().get_token() == ARM::Tokens::Token::HEX_NUMBER);
    }
    SUBCASE("token is a decimal number") {
        std::string line("1234");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.advance();
        CHECK(lexer.get_lexem().get_token() == ARM::Tokens::Token::DEC_NUMBER);
    }
}