#include "parser.hpp"
#include "ast.h"


namespace ARM {
    namespace Parser {
        void Parser::set_up(const std::string &path) {
            std::fstream file;
            file.open(path);
            std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
            std::stringstream ss(ir);

            lexer = new Lexer::Lexer(ss);
        }

        void Parser::assign_program() {

        }
    }


}