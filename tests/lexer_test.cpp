#include "doctest.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "lexer.hpp"

void check_sequence(std::vector<ARM::Lexer::Lexem> lexems, std::vector<ARM::Tokens::Token> tokens) {
    for (int i = 0; i < std::min(lexems.size(), tokens.size()); i++) {
        CHECK_MESSAGE(lexems[i].get_token() == tokens[i], "Index: " << i << " Token: " << \
        lexems[i].get_token() << " Value: " << lexems[i].get_curr_lexem());
    }
}

void check_sequence(std::vector<ARM::Lexer::Lexem> lexems, std::vector<std::string> tokens) {
    for (int i = 0; i < std::min(lexems.size(), tokens.size()); i++) {
        CHECK_MESSAGE(lexems[i].get_curr_lexem().compare(tokens[i]) == 0, "Index: " << i << " Token: " << \
                                            lexems[i].get_token() << " Value: " << lexems[i].get_curr_lexem());
    }
}

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
        check_sequence(lexer.get_lexems(), {
            ARM::Tokens::Token::ARCHITECTURE,
            ARM::Tokens::Token::ARMV8_A,
            ARM::Tokens::Token::EOL_TOKEN,
            ARM::Tokens::Token::FILE,
            ARM::Tokens::Token::RAW_STRING,
            ARM::Tokens::Token::EOF_TOKEN
        });
    }
    SUBCASE("Can read fully qualified arch directive with file name and retain values") {
        std::string line(R"(.arch armv8-a
.file "test.s")");
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        lexer.run();
        
        check_sequence(lexer.get_lexems(), {
            ".arch",
            "armv8-a",
            "\n",
            ".file",
            "\"test.s\"",
            ""
        });
        
    }
}

TEST_CASE("Lexer can read files and generate lexems") {
    SUBCASE("Can read file and lex it") {
        // Read a file into a stringstream and lex it
        std::fstream file;
        const std::string path = "./test_files/partial.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        file.open(path);
        std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        std::stringstream ss(ir);

        ARM::Lexer::Lexer lexer(ss);

        lexer.run();

        CHECK(lexer.get_lexems().size() > 0);

        check_sequence(lexer.get_lexems(), {
            ARM::Tokens::Token::ARCHITECTURE, ARM::Tokens::Token::ARMV8_A, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::FILE, 
            ARM::Tokens::Token::RAW_STRING, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::TEXT, ARM::Tokens::Token::EOL_TOKEN, 
            ARM::Tokens::Token::GLOBAL, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::DATA_SECTION, 
            ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::ALIGN, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, 
            ARM::Tokens::Token::TYPE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA, ARM::Tokens::Token::OBJECT, 
            ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::SIZE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA, 
            ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOF_TOKEN});
    }
    SUBCASE("Can read a bigger file") {
        std::fstream file;
        const std::string path = "./test_files/constants.s";

        file.open(path);
        std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        std::stringstream ss(ir);

        ARM::Lexer::Lexer lexer(ss);

        lexer.run();
        // assert that tests/test_files/constants.s can be lexed with proper tokens
        CHECK(lexer.get_lexems().size() > 0);
        check_sequence(lexer.get_lexems(), {
        ARM::Tokens::Token::ARCHITECTURE, ARM::Tokens::Token::ARMV8_A, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::FILE,
        ARM::Tokens::Token::RAW_STRING, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::TEXT, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::GLOBAL, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::DATA_SECTION,
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::ALIGN, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::TYPE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA, ARM::Tokens::Token::OBJECT,
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::SIZE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA,
        ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COLON,
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::WORD, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::GLOBAL, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::ALIGN,
        ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::TYPE, ARM::Tokens::Token::LABEL,
        ARM::Tokens::Token::COMMA, ARM::Tokens::Token::OBJECT, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::SIZE,
        ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COLON, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::QUAD,
        ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::GLOBAL, ARM::Tokens::Token::LABEL,
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::TYPE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA,
        ARM::Tokens::Token::OBJECT, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::SIZE, ARM::Tokens::Token::LABEL,
        ARM::Tokens::Token::COMMA, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::LABEL,
        ARM::Tokens::Token::COLON, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::BYTE, ARM::Tokens::Token::DEC_NUMBER, 
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::GLOBAL, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::ALIGN, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::TYPE,
        ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA, ARM::Tokens::Token::OBJECT, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::SIZE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA, ARM::Tokens::Token::DEC_NUMBER,
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COLON, ARM::Tokens::Token::EOL_TOKEN,
        ARM::Tokens::Token::WORD, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::GLOBAL,
        ARM::Tokens::Token::LABEL, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::ALIGN, ARM::Tokens::Token::DEC_NUMBER,
        ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::TYPE, ARM::Tokens::Token::LABEL, ARM::Tokens::Token::COMMA,
        ARM::Tokens::Token::OBJECT, ARM::Tokens::Token::EOL_TOKEN, ARM::Tokens::Token::SIZE, ARM::Tokens::Token::LABEL,
        ARM::Tokens::Token::COMMA, ARM::Tokens::Token::DEC_NUMBER, ARM::Tokens::Token::EOL_TOKEN, 
        });

        


    }
}