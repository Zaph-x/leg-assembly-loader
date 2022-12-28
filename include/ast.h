// Generate an abstract syntax tree for the ARM assembly language based on the tokens defined in tokens.h.

#include "parser_tokens.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>


/*
namespace ARM {

    class Parser {
    public:
        explicit Parser(std::vector<Token*> tokens) : tokens(std::move(tokens)) {}
        ~Parser() = default;
        void parse() {
            for (auto token : tokens) {
                if (dynamic_cast<ArithmeticInstructionToken*>(token)) {
                    std::cout << "Arithmetic instruction: " << token->get_value() << std::endl;
                }
                else if (dynamic_cast<LogicalInstructionToken*>(token)) {
                    std::cout << "Logical instruction: " << token->get_value() << std::endl;
                }
                else if (dynamic_cast<BranchInstructionToken*>(token)) {
                    std::cout << "Branch instruction: " << token->get_value() << std::endl;
                }
                else if (dynamic_cast<StringToken*>(token)) {
                    std::cout << "String: " << token->get_value() << std::endl;
                }
                else {
                    std::cout << "Unknown" << std::endl;
                }
            }
        }
    private:
        std::vector<Token*> tokens;
    };

    void parse(std::vector<Token*> tokens) {
        Parser parser(tokens);
        parser.parse();
    }

}*/