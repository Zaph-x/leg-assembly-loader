#include "parser.hpp"

#include <memory>
#include <iostream>
#include "lexer.hpp"
#include "ast.h"

#define assert(x) if (!(x)) {std::cerr << "Parser assertion failed. " #x " did not hold true." << std::endl; throw;}


namespace ARM {
    namespace Parser {

        std::map<std::string, DefinitionStub> stub_map;

        inline void Parser::verify_stub(const std::string &stub_name) {
            if (!stub_map.contains(stub_name)) return;

            auto& stub = stub_map[stub_name];

            if (!(stub.get_name() == stub.get_name() and stub.get_size() != 0 and
                stub.get_type() != GlobalType::UNDEFINED and stub.get_values().size() > 0)) return;

            if (stub.get_type() == GlobalType::F ){
                //Function Node
            }

            if (stub.get_type() == GlobalType::O){
                Variable var_node = Variable(stub);
                this->get_program()->add_node(&var_node);
            }
        }

        void Parser::set_up(const std::string &path) {
            std::fstream file;
            file.open(path);
            std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
            std::stringstream ss(ir);
            lexer = std::make_unique<Lexer::Lexer>(ss);
            lexer->run();
            std::vector<Lexer::Lexem> lexems = lexer->get_lexems();
            lexem_stream.set_vector(lexems);
        }

        void Parser::set_up(Lexer::Lexer &lxr) {
            lexer = std::make_unique<Lexer::Lexer>(lxr);
            lexer->run();
            std::vector<Lexer::Lexem> lexems = lexer->get_lexems();
            lexem_stream.set_vector(lexems);
        }

        void Parser::assign_program() {
            set_program(Program());

            if (lexem_stream.peek().get_token() == Tokens::Token::ARCHITECTURE) {
                assign_architecture();

            }

            if (lexem_stream.peek().get_token() == Tokens::Token::FILE) {
                assign_file_name();
            }

            if (lexem_stream.peek().get_token() == Tokens::Token::TEXT_SECTION) {
                assign_text_section();
            } else throw std::runtime_error("No text section specified");

        }

        void Parser::assign_architecture() {
            assert(lexem_stream.next().get_token() == Tokens::Token::ARCHITECTURE);
            if (lexem_stream.peek().get_token() == Tokens::Token::ARMV8_A) {
                program.set_architecture(lexem_stream.next().get_curr_lexem());
                assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
            }
            else {
                throw std::runtime_error("Expected identifier after architecture");
            }
        }

        void Parser::assign_file_name() {
            assert(lexem_stream.next().get_token() == Tokens::Token::FILE);
            if (lexem_stream.peek().get_token() == Tokens::Token::RAW_STRING) {
                program.set_file_name(lexem_stream.next().get_curr_lexem());
                assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
            }
            else {
                throw std::runtime_error("Expected file name after .file directive");
            }

        }

        void Parser::assign_text_section() {
            assert(lexem_stream.next().get_token() == Tokens::Token::TEXT_SECTION);
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
        }

        void parse_object(std::map<std::string, std::string> &placeholder_values) {

        }

        void Parser::assign_global(){
            assert(lexem_stream.next().get_token() == Tokens::Token::GLOBAL)
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) throw;

            if

        }

        void Parser::nodeify(){ // Name pending
            //this->lexem_stream.


            // Functions


        }


    }


}