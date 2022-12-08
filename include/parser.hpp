#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "token.hpp"
#include "lexer.hpp"
#include "converter.hpp"

namespace ARM{
namespace Parser{
    class ASTNode {
    public:
        ASTNode() = default;
        ASTNode(Tokens::Token token, std::string lexem, int line, int possition) : token(token), lexem(lexem), line(line), possition(possition) {}
        ~ASTNode() = default;
        Tokens::Token get_token() const { return token; }
        int get_line() const { return line; }
        int get_possition() const { return possition; }

        std::string get_string_value() const { return lexem; }
        char get_char_value() const { if (get_token() == Tokens::Token::DEC_NUMBER)
                                    return (char)std::atoi(lexem.c_str()); else throw std::bad_cast(); }
        int get_int_value() const { if (get_token() == Tokens::Token::DEC_NUMBER)
                                    return std::atoi(lexem.c_str()); else throw std::bad_cast(); }
        long get_long_value() const { if (get_token() == Tokens::Token::DEC_NUMBER)
                                    return std::atol(lexem.c_str()); else throw std::bad_cast(); }
        float get_float_value() const { if (get_token() == Tokens::Token::DEC_NUMBER)
                                    return ARM::Converters::uint32_to_float(get_int_value()); else throw std::bad_cast(); }
        double get_double_value() const { if (get_token() == Tokens::Token::DEC_NUMBER)
                                    return ARM::Converters::uint64_to_double(get_long_value()); else throw std::bad_cast(); }
    private:
        Tokens::Token token;
        std::string lexem;

        int line;
        int possition;
    };
    class parser {
    public:
        parser(std::vector<ARM::Lexer::Lexem> lexems) : lexems(lexems) {
            curr_lexem = lexems.begin();
        }
        ~parser() = default;
        Lexer::Lexem get_curr_token() const { return *curr_lexem; }
        std::vector<ASTNode> get_parsed_tokens() const { return parsed_tokens; }
        void run();
    private:
        std::vector<ARM::Lexer::Lexem> lexems;
        std::vector<ASTNode> parsed_tokens;
        std::vector<ARM::Lexer::Lexem>::iterator curr_lexem;
    };
}
}