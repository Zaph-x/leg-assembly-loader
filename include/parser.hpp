#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "token.hpp"

namespace ARM{
namespace Parser{
    struct {
        ARM::Tokens::Token token;
        std::string raw_value;
    } parsed_token;
}
}