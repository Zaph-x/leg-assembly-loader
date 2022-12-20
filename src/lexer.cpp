#include "lexer.hpp"
#include <iostream>
#include <string>
#include "token.hpp"
#include "vector_stream.hpp"

// build a lexer for an input file using
namespace ARM::Lexer {
    void Lexer::advance() {
        curr_lexem = next_token();
        lexems.push_back(curr_lexem);
        buffer.clear();
    }

    void Lexer::run() {
        while (!in->eof()) {
            advance();
        }
        lexems.emplace_back(Tokens::Token::EOF_TOKEN, "", EOF, EOF);
        buffer.clear();
    }

    char Lexer::get_next_char()
    {
        if (in->eof()) {
            return EOF;
        }
        char c = (char)in->get();
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
        if ((c == '/' and in->peek() == '/') or c == '#' or c == ';')
        {
            in->ignore(1000, '\n');
            c = '\n';
            line++;
            position = 0;
        }
        return c;
    }

    Lexem error(const std::string& buffer, const int line, const int position) {
        std::cout << "Error: " << buffer << " " << line << " " << position << std::endl;
        return {Tokens::Token::ERROR, buffer, line, position};
    }

    Lexem Lexer::next_token()
    {
        while (char c = get_next_char())
        {
            if (c == EOF or in->eof()) return {Tokens::Token::EOF_TOKEN, "", line, position};
            while (isspace(c)){
                if (c == '\n')
                    return {Tokens::Token::EOL_TOKEN, "\n", line, position};
                c = get_next_char();
            }
            if (c == '.') {
                buffer += c;
                while (!isspace(in->peek()) and in->peek() != '.' and in->peek() != ',') {
                    buffer += (char)in->get();
                }

                if (buffer.ends_with(':') or buffer.starts_with(".L")) {
                    known_labels[buffer] = {Tokens::Token::LABEL, buffer, line, position};
                    return known_labels[buffer];
                }
                else if (Tokens::section_map.contains(buffer)) {
                    return {Tokens::section_map[buffer], buffer, line, position};
                }
                else if (Tokens::cfi_map.contains(buffer)) {
                    return {Tokens::cfi_map[buffer], buffer, line, position};
                }
                else if (Tokens::directives_map.contains(buffer)) {
                    return {Tokens::directives_map[buffer], buffer, line, position};
                }
                else if (buffer.starts_with(".-")) {
                    if (known_labels.find(buffer.substr(2)) != known_labels.end()) {
                        return known_labels[buffer.substr(2)];
                    }
                }

            }
            else if (c == '@') {
                buffer += c;
                while (!isspace(in->peek()) and in->peek() != '.' and in->peek() != ',') {
                    buffer += (char)in->get();
                }
                if (buffer == "@progbits") return {Tokens::Token::PROGBITS, buffer, line, position};

            }
            else if (isprint(c)) {
                if (c == ',') return {Tokens::Token::COMMA, ",", line, position};

                if (Tokens::symbols_map.contains(c)){
                    return {Tokens::symbols_map[c], std::string(1, c), line, position};
                }

                if ((c == 'w' or c == 'x' or c == 'v' or c == 's' or c == 'd'  or c == 'b' or c == 'h') and std::isdigit(in->peek())) {
                    buffer += c;
                    while (isalnum(in->peek())) {
                        buffer += (char)in->get();
                    }
                    if (Tokens::registers_map.contains(buffer)) {
                        return {Tokens::registers_map[buffer], buffer, line, position};
                    }
                }
                if (c == '0' and in->peek() == 'x') {
                    buffer += c;
                    buffer += (char)in->get();
                    while (isxdigit(in->peek())) {
                        buffer += (char)in->get();
                    }
                    return {Tokens::Token::HEX_NUMBER, buffer, line, position};
                }
                if (isdigit(c)) {
                    buffer += c;
                    while (isdigit(in->peek())) {
                        buffer += (char)in->get();
                    }
                    return {Tokens::Token::DEC_NUMBER, buffer, line, position};
                }
                if (c == '"') {
                    buffer += c;
                    while (in->peek() != '"' and buffer.back() != '\\') {
                        buffer += (char)in->get();
                    }
                    buffer += (char)in->get();
                    return {Tokens::Token::RAW_STRING, buffer, line, position};
                }
                else {
                    buffer += c;
                    while (!isspace(in->peek()) and in->peek() != EOF and in->peek() != '\n' and in-> peek() != ',') {
                        buffer += (char)in->get();
                    }
                    if (buffer == "armv8-a") {
                        return {Tokens::Token::ARMV8_A, buffer, line, position};
                    }
                    else if (buffer.ends_with(':')) {
                        buffer.pop_back();
                        known_labels[buffer] = {Tokens::Token::LABEL, buffer, line, position};
                        return known_labels[buffer];
                    }
                    else if (Tokens::type_map.contains(buffer)) return {Tokens::type_map[buffer], buffer, line, position};
                    else if (Tokens::instructions_map.contains(buffer) and lexems.back().get_token() != Tokens::Token::GLOBAL \
                            and lexems.back().get_token() != Tokens::Token::SIZE and lexems.back().get_token() != Tokens::Token::ALIGN \
                            and lexems.back().get_token() != Tokens::Token::TYPE and lexems.back().get_token() != Tokens::Token::COMMA) return {Tokens::instructions_map[buffer], buffer, line, position};
                    else if (known_labels.contains(buffer)) return known_labels[buffer];
                    else if (lexems.back().get_token() == Tokens::Token::GLOBAL and !known_labels.contains(buffer)) {
                        known_labels[buffer] = {Tokens::Token::IDENTIFIER, buffer, line, position};
                        return known_labels[buffer];
                    } else if (lexems.back().get_token() == Tokens::Token::GLOBAL and known_labels.contains(buffer))
                        return {Tokens::Token::IDENTIFIER, buffer, line, position};
                    else if (buffer.starts_with(".-")) {
                        if (known_labels.find(buffer.substr(2)) != known_labels.end()) {
                            return known_labels[buffer.substr(2)];
                        } else {
                            /* Should ever only happen if function is not defined, yet the range is */
                            return error(buffer, line, position);
                        }
                    }
                }
            } else return error(buffer, line, position);
        }
        return {Tokens::Token::EOF_TOKEN, "", line, position};
    }
}

