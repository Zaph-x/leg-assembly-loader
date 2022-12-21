#include "parser.hpp"

#include <memory>
#include <iostream>
#include "lexer.hpp"
#include "ast.h"

#define assert(x) if (!(x)) {std::cerr << "Parser assertion failed. " #x " did not hold true." << std::endl; throw;}


namespace ARM {
    namespace Parser {

        std::map<std::string, DefinitionStub> stub_map;

        void Parser::verify_stub(const std::string &stub_name) {
            if (!stub_map.contains(stub_name)) return;

            auto& stub = stub_map[stub_name];

            if (!(stub.get_name() == stub.get_name() and (stub.get_type() == GlobalType::F or stub.get_size() != 0) and
                stub.get_type() != GlobalType::UNDEFINED and !stub.get_values().empty())) return;

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

            while(lexem_stream.has_next()) {
                switch (lexem_stream.peek().get_token()) {
                    case Tokens::Token::ARCHITECTURE:
                        assign_architecture();
                        break;
                    case Tokens::Token::FILE:
                        assign_file_name();
                        break;
                    case Tokens::Token::TEXT_SECTION:
                        assign_text_section();
                        break;
                    case Tokens::Token::GLOBAL:
                        assign_global();
                        break;
                    case Tokens::Token::SIZE:
                        assign_global_size();
                        break;
                    case Tokens::Token::TYPE:
                        assign_type();
                        break;
                    case Tokens::Token::LABEL:
                        handle_label();
                        break;

                    default:
                        lexem_stream.next();
                }
            }
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

        bool Parser::has_identifier(const std::string &name) {
            return this->get_program()->has_variable_definition(name) || this->get_program()->has_function_definition(name);
        }

        void Parser::assign_global(){
            assert(lexem_stream.next().get_token() == Tokens::Token::GLOBAL)
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) throw;

            if (this->has_identifier(lexem_stream.peek().get_curr_lexem()))
                throw std::runtime_error("Identifier already defined");

            auto lxm = lexem_stream.next();

            if (!stub_map.count(lxm.get_curr_lexem())) {
                stub_map[lxm.get_curr_lexem()] = DefinitionStub(lxm.get_curr_lexem());
                this->verify_stub(lxm.get_curr_lexem());
                return;
            }

        }

        void Parser::assign_global_size() {
            assert(lexem_stream.next().get_token() == Tokens::Token::SIZE)
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) throw;
            auto idnt = lexem_stream.next();
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)

            if (lexem_stream.peek().get_token() != Tokens::Token::DEC_NUMBER) throw;
            auto size = lexem_stream.next();

            if (!stub_map.count(idnt.get_curr_lexem())) {
                stub_map[idnt.get_curr_lexem()] = DefinitionStub(idnt.get_curr_lexem());
            }
            stub_map[idnt.get_curr_lexem()].set_size(std::atoi(size.get_curr_lexem().c_str()));
            this->verify_stub(idnt.get_curr_lexem());
        }

        void Parser::assign_type() {
            assert(lexem_stream.next().get_token() == Tokens::Token::TYPE)
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) throw;
            auto idnt = lexem_stream.next();
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)

            if (lexem_stream.peek().get_token() != Tokens::Token::OBJECT
                    and lexem_stream.peek().get_token() != Tokens::Token::FUNCTION
                    and lexem_stream.peek().get_token() != Tokens::Token::TLS_OBJECT) throw;
            auto type = lexem_stream.next();

            if (!stub_map.count(idnt.get_curr_lexem())) {
                stub_map[idnt.get_curr_lexem()] = DefinitionStub(idnt.get_curr_lexem());
            }
            switch (type.get_token()) {
                case Tokens::Token::OBJECT: stub_map[idnt.get_curr_lexem()].set_type(GlobalType::O); break;
                case Tokens::Token::FUNCTION: stub_map[idnt.get_curr_lexem()].set_type(GlobalType::F); break;
                case Tokens::Token::TLS_OBJECT: stub_map[idnt.get_curr_lexem()].set_type(GlobalType::T); break;
                default: throw;
            }
            this->verify_stub(idnt.get_curr_lexem());

        }

        void Parser::handle_function() {
            assert(lexem_stream.next().get_token() == Tokens::Token::FUNC_BEGIN_LABEL)
            auto function = lexem_stream.next();
            bool unknown = false;
            if(!stub_map.contains(function.get_curr_lexem())){
                stub_map[function.get_curr_lexem()] = DefinitionStub(function.get_curr_lexem());
                unknown = true;
            }
            if (unknown and lexem_stream.peek().get_token() == Tokens::Token::FUNC_BEGIN_LABEL) {

                stub_map[function.get_curr_lexem()].set_type(GlobalType::F);
                handle_function();
                this->verify_stub(function.get_curr_lexem());
                return;
            }
            assign_value(function.get_curr_lexem());

            this->verify_stub((function.get_curr_lexem()));

            return;
        }

        void Parser::handle_label() {
            assert(lexem_stream.peek().get_token() == Tokens::Token::LABEL)
            auto label = lexem_stream.next();
            bool unknown = false;
            if (!stub_map.contains(label.get_curr_lexem())) {
                stub_map[label.get_curr_lexem()] = DefinitionStub(label.get_curr_lexem());
                unknown = true;
            }
            if (unknown and lexem_stream.peek().get_token() == Tokens::Token::FUNC_BEGIN_LABEL) {

                stub_map[label.get_curr_lexem()].set_type(GlobalType::F);
                handle_function();
                this->verify_stub(label.get_curr_lexem());
                return;
            }
            assign_value(label.get_curr_lexem());
            this->verify_stub(label.get_curr_lexem());
        }

        void Parser::handle_multi_word(const std::string &ref_name) {
            if (lexem_stream.peek().get_token() != Tokens::Token::WORD) return;
            stub_map[ref_name].set_size(4 + stub_map[ref_name].get_size());
            lexem_stream.next();
            assert(lexem_stream.peek().get_token() == Tokens::Token::DEC_NUMBER)
            stub_map[ref_name].get_values().push_back(lexem_stream.next().get_curr_lexem());
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
            handle_multi_word(ref_name);
        }

        void Parser::assign_value(int expected_size, Tokens::Token expected_type, const std::string &ref_name) {
            if (stub_map.contains(ref_name) and stub_map[ref_name].get_size() == 0)
                stub_map[ref_name].set_size(expected_size);
            assert(lexem_stream.peek().get_token() == expected_type)
            stub_map[ref_name].get_values().push_back(lexem_stream.next().get_curr_lexem());
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
        }

        void Parser::assign_value(const std::string &ref_name) {
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
            switch (lexem_stream.next().get_token()) {
                case Tokens::Token::HWORD: {
                    assign_value(2, Tokens::Token::DEC_NUMBER, ref_name);
                    return;
                }
                case Tokens::Token::BYTE: {
                    assign_value(1, Tokens::Token::DEC_NUMBER, ref_name);
                    return;
                }
                case Tokens::Token::WORD: {
                    assign_value(4, Tokens::Token::DEC_NUMBER, ref_name);
                    handle_multi_word(ref_name);
                    return;
                }
                case Tokens::Token::FLOAT: {
                    assign_value(4, Tokens::Token::DEC_NUMBER, ref_name);
                    return;
                }
                case Tokens::Token::QUAD:
                case Tokens::Token::DOUBLE: {
                    if (stub_map.contains(ref_name) and stub_map[ref_name].get_size() == 0)
                        stub_map[ref_name].set_size(8);
                    if (lexem_stream.peek().get_token() == Tokens::Token::DEC_NUMBER
                            or lexem_stream.peek().get_token() == Tokens::Token::IDENTIFIER)
                    {
                        stub_map[ref_name].get_values().push_back(lexem_stream.next().get_curr_lexem());
                        assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
                        return;
                    }

                }
                case Tokens::Token::OCTA: {
                    assign_value(16, Tokens::Token::DEC_NUMBER, ref_name);
                    return;
                }
                case Tokens::Token::STRING: {
                    assign_value(8, Tokens::Token::RAW_STRING, ref_name);
                }
                default: throw;
            }
        }

        void Parser::nodeify(){ // Name pending
            //this->lexem_stream.


            // Functions


        }


    }


}