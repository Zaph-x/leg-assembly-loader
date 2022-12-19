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
    class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        void set_up(const std::string &path);
        void assign_program();

    private:
        Lexer::Lexer* lexer;
    };
}
}