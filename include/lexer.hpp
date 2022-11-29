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
        bool is_valid_char(int c);
        std::vector<std::string> tokens;
        void read_instruction(const std::string &line, int &line_offset);
        void read_register(const std::string &line, int &line_offset);
        void read_label(const std::string &line, int &line_offset);
        void read_value(const std::string &line, int &line_offset);
    }

enum class Opcodes
{
    
};
}

#endif