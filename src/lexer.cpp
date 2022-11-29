#include "lexer.hpp"
#include <iostream>
#include "token.hpp"

// build a lexer for an input file using
namespace ARM
{
    namespace Lexer
    {
        void Lexer::advance() {
            curr_lexem = next_token();
            lexems.push_back(curr_lexem);
        }

        char Lexer::get_next_char()
        {
            char c = in->get();
            if (c == '\n')
            {
                line++;
                position = 0;
            }
            else
            {
                position++;
            }
            // check for comments
            if ((c == '/' && in->peek() == '/') || c == '#' || c == ';' || c == '@')
            {
                in->ignore(1000, '\n');
                c = '\n';
                line++;
                position = 0;
            }
            return c;
        }

        Lexem Lexer::next_token()
        {
            int c;
            while (char c = get_next_char())
            {
                if (c == EOF) return Lexem(Tokens::Token::EOF_TOKEN, "", line, position);
                while (isspace(c)){
                    if (c == '\n') 
                        return Lexem(Tokens::Token::EOL_TOKEN, "\n", line, position);
                    c = get_next_char();
                }

                if (isprint(c)) {
                    if (Tokens::symbols_map.contains(c)){
                        return Lexem(Tokens::symbols_map[c], std::string(1, c), line, position);
                    }
                    if (c == 'w' || c == 'x' || c == 'v' || c == 's' || c == 'd'  || c == 'b' || c == 'h') {
                        buffer += c;
                        while (isalnum(in->peek())) {
                            buffer += in->get();
                        }
                        if (Tokens::registers_map.contains(buffer)) {
                            return Lexem(Tokens::registers_map[buffer], buffer, line, position);
                        }
                        else {
                            return Lexem(Tokens::Token::ERROR, buffer, line, position);
                        }
                    }
                    if (c == '0' && in->peek() == 'x') {
                        buffer += c;
                        buffer += in->get();
                        while (isxdigit(in->peek())) {
                            buffer += in->get();
                        }
                        return Lexem(Tokens::Token::HEX_NUMBER, buffer, line, position);
                    }
                    if (isdigit(c)) {
                        buffer += c;
                        while (isdigit(in->peek())) {
                            buffer += in->get();
                        }
                        return Lexem(Tokens::Token::DEC_NUMBER, buffer, line, position);
                    }
                    if (c == '"') {
                        buffer += c;
                        while (in->peek() != '"' && buffer.back() != '\\') {
                            buffer += in->get();
                        }
                        buffer += in->get();
                        return Lexem(Tokens::Token::STRING, buffer, line, position);
                    }
                    if (c == '.') {
                        buffer += c;
                        while (isalnum(in->peek()) || in->peek() == '_') {
                            buffer += in->get();
                        }
                        if (Tokens::directives_map.contains(buffer)) {
                            return Lexem(Tokens::directives_map[buffer], buffer, line, position);
                        }
                        else {
                            return Lexem(Tokens::Token::ERROR, buffer, line, position);
                        }
                    }
                }
            }
            return Lexem(Tokens::Token::EOF_TOKEN, "", line, position);
        }
    }
}

