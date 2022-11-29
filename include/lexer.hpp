#ifndef ARM_LEXER_HPP
#define ARM_LEXER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "token.hpp"

namespace ARM{
    namespace Lexer{

        class Lexer {
            public:
                Lexer(std::istream &input) : in(&input) {
                    line = 1;
                    position = 0;
                    advance();
                }
            private:
                std::istream *in;
                int line;
                int position;
                std::string buffer;
                Tokens::Token current_token;
        int getLine() const { return line; }
        int getPosition() const { return position; }
        void advance() {current_token = next_token();}
        Tokens::Token next_token();
        bool is_valid_char(int c);
        std::vector<std::string> tokens;
        void read_instruction(const std::string &line, int &line_offset);
        void read_register(const std::string &line, int &line_offset);
        void read_label(const std::string &line, int &line_offset);
        void read_value(const int &line, int &line_offset);
        void read_character(const char &c, int &line_offset);
    };

    }

}

#endif