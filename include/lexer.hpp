#ifndef ARM_LEXER_HPP
#define ARM_LEXER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "token.hpp"
#include <map>

namespace ARM{
    namespace Lexer{
        class Lexem {
            public:
                Lexem() = default;
                Lexem(Tokens::Token token, std::string lexem, int line, int possition) : token(token), lexem(lexem), line(line), possition(possition) {}
                ~Lexem() = default;
                Tokens::Token get_token() const { return token; }
                std::string get_curr_lexem() const { return lexem; }
                int get_line() const { return line; }
                int get_possition() const { return possition; }
            private:
                Tokens::Token token;
                std::string lexem;
                int line;
                int possition;
        };
        class Lexer {
            public:
                Lexer(std::istream &input) : in(&input) {
                    line = 1;
                    position = 0;
                }
                ~Lexer() = default;
                int get_line() const { return line; }
                int get_position() const { return position; }
                Lexem get_curr_lexem() const { return curr_lexem; }
                std::vector<Lexem> get_lexems() const { return lexems; }
                Lexem next_token();
                void advance();
                void run();
            private:
                std::istream *in;
                int line;
                int position;
                std::string buffer;
                Lexem curr_lexem;
                bool is_valid_char(int c);
                char get_next_char();

                bool is_string;        
                std::vector<Lexem> lexems;
                void read_instruction(const std::string &line, int &line_offset);
                void read_register(const std::string &line, int &line_offset);
                void read_label(const std::string &line, int &line_offset);
                void read_value(const int &line, int &line_offset);
                void read_character(const char &c, int &line_offset);
        };

    }

}

#endif