#include "doctest.h"
#include "parser.hpp"


TEST_CASE("Parsed tokens can get proper values") {
    SUBCASE("Can get proper value for a string in a token") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::RAW_STRING, "Hello world", 0, 0);
        CHECK(token.get_string_value().compare("Hello world") == 0);
    }
    SUBCASE("Can get proper value for a char in a token") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::DEC_NUMBER, "65", 0, 0);
        CHECK(token.get_char_value() == 'A');
    }
    SUBCASE("Can get proper value for a int in a token") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::DEC_NUMBER, "65", 0, 0);
        CHECK(token.get_int_value() == 65);
    }
    SUBCASE("Can get proper value for a float in a token") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::DEC_NUMBER, "1067320914", 0, 0);
        CHECK(token.get_float_value() == 1.2345678806304931640625E0);
    }
    SUBCASE("Can not get int value for a raw string") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::RAW_STRING, "Hello world", 0, 0);
        CHECK_THROWS(token.get_int_value());
    }
    SUBCASE("Can not get float value for a raw string") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::RAW_STRING, "Hello world", 0, 0);
        CHECK_THROWS(token.get_float_value());
    }
    SUBCASE("Can not get char value for a raw string") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::RAW_STRING, "Hello world", 0, 0);
        CHECK_THROWS(token.get_char_value());
    }
    SUBCASE("Can get not int value for a hex number") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::HEX_NUMBER, "0x1234", 0, 0);
        CHECK_THROWS(token.get_int_value());
    }
    SUBCASE("Can get not float value for a hex number") {
        ARM::Parser::parsed_token token(ARM::Tokens::Token::HEX_NUMBER, "0x1234", 0, 0);
        CHECK_THROWS(token.get_float_value());
    }
}