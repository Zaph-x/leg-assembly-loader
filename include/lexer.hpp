#ifndef ARM_LEXER_HPP
#define ARM_LEXER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include "token.hpp"
#include "vector_stream.hpp"
#include <map>

namespace ARM::Lexer{
        class Lexem {
            public:
                Lexem() = default;
                Lexem(Tokens::Token token, std::string lexem, int line, int possition) : token(token), lexem(std::move(lexem)), line(line), possition(possition) {}
                ~Lexem() = default;
                [[nodiscard]] Tokens::Token get_token() const { return token; }
                [[nodiscard]] std::string get_curr_lexem() const { return lexem; }
                [[nodiscard]] int get_line() const { return line; }
                [[nodiscard]] int get_possition() const { return possition; }
            private:
                Tokens::Token token;
                std::string lexem;
                int line{};
                int possition{};
        };
        class Lexer {
            public:
                Lexer(std::istream &input) : in(&input) {
                    line = 1;
                    position = 0;
                }
                ~Lexer() = default;
                [[nodiscard]] int get_line() const { return line; }
                [[nodiscard]] int get_position() const { return position; }
                [[nodiscard]] Lexem get_curr_lexem() const { return curr_lexem; }
                [[nodiscard]] std::vector<Lexem> get_lexems() const { return lexems; }
                Lexem next_token();
                void advance();
                void run();
            private:
                std::istream *in;
                int line;
                int position;
                std::string buffer;
                Lexem curr_lexem;
                char get_next_char();
                std::vector<Lexem> lexems;
                std::map<std::string, Lexem> known_labels;
        };

    }

#endif