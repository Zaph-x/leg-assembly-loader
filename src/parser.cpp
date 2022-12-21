#include "parser.hpp"

#include <memory>
#include <iostream>
#include "lexer.hpp"
#include "ast.h"

#define assert(x) if (!(x)) {std::cerr << "Parser assertion failed. " #x " did not hold true." << std::endl; throw;}


namespace ARM {
    namespace Parser {

        std::map<std::string, DefinitionStub> stub_map;

        inline void verify_stub(const std::string &stub_name) {
            if (!stub_map.contains(stub_name)) return;
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
            assert(lexem_stream.next().get_token() == Tokens::Token::GLOBAL);
            std::map<std::string, std::string> placeholder_values;

            if (lexem_stream.peek().get_token() == Tokens::Token::IDENTIFIER){
                placeholder_values["name"] = lexem_stream.next().get_curr_lexem();
                while (lexem_stream.peek().get_token() != Tokens::Token::TYPE_DIRECTIVE) lexem_stream.next();

                assert(lexem_stream.next().get_token() == Tokens::Token::TYPE_DIRECTIVE)
                auto lexem = lexem_stream.next();
                assert(lexem.get_token() == Tokens::Token::IDENTIFIER
                            && placeholder_values["name"] == lexem.get_curr_lexem())
                assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
                switch (lexem_stream.next().get_token()) {
                    case Tokens::Token::FUNCTION:
                        placeholder_values["type"] = "f"; break;
                    case Tokens::Token::OBJECT:
                        placeholder_values["type"] = "o"; parse_object(placeholder_values); break;
                    case Tokens::Token::TLS_OBJECT:
                        placeholder_values["type"] = "t"; break;
                    default:
                        throw std::runtime_error("Type value not supported");
                }


            }
        }

        void Parser::nodeify(){ // Name pending
            //this->lexem_stream.


            // Functions


        }


    }


}