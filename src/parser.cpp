#include "parser.hpp"

#include <memory>
#include <iostream>
#include "lexer.hpp"
#include "ast.h"



namespace ARM::Parser {

#define assert(x) if (!(x)) {std::cerr << "Parser assertion failed. " #x " did not hold true. "<< std::endl \
                    << "    @ " << __FILE__ << ":" << __LINE__ << std::endl \
                    << "    Token: '" << lexem_stream.previous().get_curr_lexem() << "' " << lexem_stream.previous().get_token() << std::endl; throw std::exception();}

#define asserteq(x, y) if (!((x)==(y))) {std::cerr << "Parser assertion failed. " << x << " == " << y << " did not hold true. "<< std::endl \
                    << "    @ " << __FILE__ << ":" << __LINE__ << std::endl                                                                 \
                    << "    S LINE: " << lexem_stream.previous().get_line() << ":" << lexem_stream.previous().get_possition() << std::endl                                                                                                                        \
                    << "    Token: '" << lexem_stream.previous().get_curr_lexem() << "' " << lexem_stream.previous().get_token() << std::endl; throw std::exception();}

#define ERROR(lxm, msg) Parser::error(__LINE__, lxm, msg)


        void Parser::error(int line ,const Lexer::Lexem &lxm, const std::string &msg) {
            std::cerr << "Parser error: " << msg << std::endl
                    << "    at " << lxm.get_line() << ":" << lxm.get_possition() << std::endl
                    << "    -> =" << lxm.get_curr_lexem() << "= '" << lxm.get_token() << "'"  << std::endl
                    << "    in " << __FILE__ << ":" << line << std::endl;
            throw std::exception();
        }

        std::map<std::string, DefinitionStub> stub_map;

        void Parser::verify_stub(const std::string &stub_name) {
            // check if stub_map contains stub_name
            if (stub_map.find(stub_name) == stub_map.end()) {
                std::cerr << "Parser error: Stub '" << stub_name << "' not found." << std::endl;
                throw std::exception();
            }
            auto stub = stub_map[stub_name];
            if (stub.get_type() == GlobalType::UNDEFINED) return;
            if (stub.get_type() == GlobalType::F) return;
            if (stub.get_type() == GlobalType::REF) {
                if (stub.get_size() == 0) return;
                if (stub.get_values().size() == 0) return;
                program->add_variable(std::make_shared<Variable>(stub));
                return;
            }
            if (stub.get_type() == GlobalType::O) {
                if (stub.get_size() == 0) return;
                if (stub.get_values().size() == 0) return;
                program->add_variable(std::make_shared<Variable>(stub));
                if (stub_map.contains(stub.get_values().front() + ":")) {
                    auto stub2 = stub_map[stub.get_values().front() + ":"];
                    if (stub2.get_type() == GlobalType::UNDEFINED) {
                        stub2.set_name(stub.get_values().front());
                        stub2.set_type(GlobalType::O);
                        stub2.set_size(8);
                        stub_map[stub2.get_name()] = stub2;
                        // remove old stub
                        stub_map.erase(stub.get_values().front() + ":");
                        verify_stub(stub2.get_name());
                        program->get_variable(stub.get_name())->set_type(GlobalType::REF);
                    }
                }
                stub_map.erase(stub.get_name());
                return;
            }
            ERROR(lexem_stream.previous(), "Stub type not supported.");
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
            std::shared_ptr<Program> program_node(new Program);
            set_program(program_node);

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
                program->set_architecture(lexem_stream.next().get_curr_lexem());
                assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
            }
            else {
                ERROR(lexem_stream.current(), "Expected identifier after architecture");
            }
        }

        void Parser::assign_file_name() {
            assert(lexem_stream.next().get_token() == Tokens::Token::FILE);
            if (lexem_stream.peek().get_token() == Tokens::Token::RAW_STRING) {
                program->set_file_name(lexem_stream.next().get_curr_lexem());
                assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
            }
            else {
                ERROR(lexem_stream.current(), "Expected file name after .file directive");
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
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) ERROR(lexem_stream.current(), "Expected identifier after .global directive");

            if (this->has_identifier(lexem_stream.peek().get_curr_lexem()))
                ERROR(lexem_stream.current(), "Identifier already defined");

            auto lxm = lexem_stream.next();

            if (!stub_map.count(lxm.get_curr_lexem())) {
                stub_map[lxm.get_curr_lexem()] = DefinitionStub(lxm.get_curr_lexem());
                this->verify_stub(lxm.get_curr_lexem());
                assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
                return;
            }
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);

        }

        void Parser::assign_global_size() {
            assert(lexem_stream.next().get_token() == Tokens::Token::SIZE)
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) ERROR(lexem_stream.current(), "Expected identifier after .size directive");
            auto idnt = lexem_stream.next();
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)

            if (lexem_stream.peek().get_token() != Tokens::Token::DEC_NUMBER) ERROR(lexem_stream.current(), "Expected decimal number after .size directive");
            auto size = lexem_stream.next();

            if (!stub_map.count(idnt.get_curr_lexem())) {
                stub_map[idnt.get_curr_lexem()] = DefinitionStub(idnt.get_curr_lexem());
            }
            int size_int = std::stoi(size.get_curr_lexem());
            stub_map[idnt.get_curr_lexem()].set_size(size_int);
            this->verify_stub(idnt.get_curr_lexem());
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
        }

        void Parser::assign_type() {
            assert(lexem_stream.next().get_token() == Tokens::Token::TYPE)
            if (lexem_stream.peek().get_token() != Tokens::Token::IDENTIFIER) ERROR(lexem_stream.current(), "Expected identifier after .type directive");
            auto idnt = lexem_stream.next();
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)

            if (lexem_stream.peek().get_token() != Tokens::Token::OBJECT
                    and lexem_stream.peek().get_token() != Tokens::Token::FUNCTION
                    and lexem_stream.peek().get_token() != Tokens::Token::TLS_OBJECT) ERROR(lexem_stream.current(), "Expected object, function or tls_object after .type directive");
            auto type = lexem_stream.next();

            if (!stub_map.count(idnt.get_curr_lexem())) {
                stub_map[idnt.get_curr_lexem()] = DefinitionStub(idnt.get_curr_lexem());
            }
            switch (type.get_token()) {
                case Tokens::Token::OBJECT: stub_map[idnt.get_curr_lexem()].set_type(GlobalType::O); break;
                case Tokens::Token::FUNCTION: stub_map[idnt.get_curr_lexem()].set_type(GlobalType::F); break;
                case Tokens::Token::TLS_OBJECT: stub_map[idnt.get_curr_lexem()].set_type(GlobalType::T); break;
                default: ERROR(lexem_stream.current(), "Expected object, function or tls_object after .type directive");
            }
            this->verify_stub(idnt.get_curr_lexem());

            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
        }

        void Parser::handle_function(const std::string &ref_name) {
            assert(lexem_stream.next().get_token() == Tokens::Token::FUNC_BEGIN_LABEL)
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
            bool unknown = false;
            if(!stub_map.contains(ref_name)){
                stub_map[ref_name] = DefinitionStub(ref_name);
                unknown = true;
            }
            stub_map[ref_name].set_type(GlobalType::F);
            std::shared_ptr<Function> func = std::make_unique<Function>(stub_map[ref_name]);
            program->add_function(std::move(func));
            Parser::assign_instructions(ref_name);
            this->verify_stub(ref_name);
            assert(lexem_stream.next().get_token() == Tokens::Token::SIZE)
            assert(lexem_stream.next().get_token() == Tokens::Token::LABEL)
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            assert(lexem_stream.next().get_token() == Tokens::Token::LABEL)
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)

        }

        void Parser::handle_label() {
            assert(lexem_stream.peek().get_token() == Tokens::Token::LABEL)
            auto label = lexem_stream.next();
            if (!stub_map.contains(label.get_curr_lexem())) {
                stub_map[label.get_curr_lexem()] = DefinitionStub(label.get_curr_lexem());
            }
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
            if (lexem_stream.peek().get_token() == Tokens::Token::FUNC_BEGIN_LABEL) {

                stub_map[label.get_curr_lexem()].set_type(GlobalType::F);
                handle_function(label.get_curr_lexem());
                this->verify_stub(label.get_curr_lexem());
                return;
            } else assign_value(label.get_curr_lexem());
            this->verify_stub(label.get_curr_lexem());
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN);
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
            asserteq(lexem_stream.peek().get_token(), expected_type)
            stub_map[ref_name].add_value(lexem_stream.next().get_curr_lexem());
        }

        void Parser::assign_value(const std::string &ref_name) {
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
                case Tokens::Token::QUAD: {
                    if (lexem_stream.peek().get_token() == Tokens::Token::LABEL) {
                        assign_value(8, Tokens::Token::LABEL, ref_name);
                        return;
                    }
                    assign_value(8, Tokens::Token::DEC_NUMBER, ref_name);
                    return;
                }
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
                    return;
                }
                default: ERROR(lexem_stream.previous(), "Expected .hword, .byte, .word, .float, .double, .quad or .octa after .global");
            }
        }

        void Parser::nodeify(){ // Name pending
            //this->lexem_stream.


            // Functions


        }

        void Parser::parse_arithmetic(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::move(std::make_unique<Register>(reg.get_curr_lexem())));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto reg2 = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg2.get_curr_lexem()))
            instr->add_arg(std::move(std::make_unique<Register>(reg2.get_curr_lexem())));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            if (val.get_token() == Tokens::Token::DEC_NUMBER) {
                instr->add_arg(std::move(std::make_unique<ImmediateValue>(val.get_curr_lexem())));
            } else if (Tokens::registers_map.contains(val.get_curr_lexem())) {
                instr->add_arg(std::move(std::make_unique<Register>(val.get_curr_lexem())));
            } else if (val.get_token() == Tokens::Token::LABEL) {
                instr->add_arg(std::move(std::make_unique<Label>(val.get_curr_lexem())));
            } else ERROR(val, "Expected register or immediate value");
        }

        void Parser::parse_mov(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::move(std::make_unique<Register>(reg.get_curr_lexem())));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            if (val.get_token() == Tokens::Token::DEC_NUMBER) {
                instr->add_arg(std::move(std::make_unique<ImmediateValue>(val.get_curr_lexem())));
            } else if (Tokens::registers_map.contains(val.get_curr_lexem())) {
                instr->add_arg(std::move(std::make_unique<Register>(val.get_curr_lexem())));
            } else ERROR(val, "Expected register or immediate value");
        }

        void Parser::parse_load(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::move(std::make_unique<Register>(reg.get_curr_lexem())));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            assert(val.get_token() == Tokens::Token::L_BRACKET)
            auto regstr = lexem_stream.next();
            assert(Tokens::registers_map.contains(regstr.get_curr_lexem()))
            val = lexem_stream.next();
            if (val.get_token() == Tokens::Token::COMMA) {
                val = lexem_stream.next();
                assert(val.get_token() == Tokens::Token::DEC_NUMBER)
                assert(lexem_stream.next().get_token() == Tokens::Token::R_BRACKET)
                if (lexem_stream.peek().get_token() == Tokens::Token::EXCLAMATION) {
                    instr->add_arg(std::make_shared<UpdatingMemoryAccess>(
                            std::make_shared<Register>(regstr.get_curr_lexem()),
                            std::make_shared<ImmediateValue>(val.get_curr_lexem())));
                } else {
                    instr->add_arg(std::make_shared<MemoryAccess>(
                            std::make_shared<Register>(regstr.get_curr_lexem()),
                            std::make_shared<ImmediateValue>(val.get_curr_lexem())));
                }
            } else if (val.get_token() == Tokens::Token::R_BRACKET) {
                instr->add_arg(std::make_shared<MemoryAccess>(
                        std::make_shared<Register>(regstr.get_curr_lexem()),
                        std::make_shared<ImmediateValue>("0")));
                if (lexem_stream.peek().get_token() == Tokens::Token::EOL_TOKEN) return;

                asserteq(lexem_stream.next().get_token(), Tokens::Token::COMMA)
                val = lexem_stream.next();
                instr->add_arg(std::make_shared<ImmediateValue>(val.get_curr_lexem()));
            } else ERROR(val, "Expected ',' or ']' after register");

        }

        void Parser::parse_pair_instruction(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(reg.get_curr_lexem()));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(reg.get_curr_lexem()));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            assert(val.get_token() == Tokens::Token::L_BRACKET)
            auto regstr = lexem_stream.next();
            assert(Tokens::registers_map.contains(regstr.get_curr_lexem()))
            auto nxt = lexem_stream.next();
            if (nxt.get_token() == Tokens::Token::R_BRACKET) {
                instr->add_arg(std::make_shared<MemoryAccess>
                                       (std::make_shared<Register>(regstr.get_curr_lexem()),
                                        std::make_shared<ImmediateValue>("0")));
                nxt = lexem_stream.next();
                assert(nxt.get_token() == Tokens::Token::COMMA)
                nxt = lexem_stream.next();
                assert(nxt.get_token() == Tokens::Token::DEC_NUMBER)
                instr->add_arg(std::make_shared<ImmediateValue>(nxt.get_curr_lexem()));
            } else {
                assert(nxt.get_token() == Tokens::Token::COMMA)
                auto offset = lexem_stream.next();
                assert(offset.get_token() == Tokens::Token::DEC_NUMBER)
                assert(lexem_stream.next().get_token() == Tokens::Token::R_BRACKET)
                if (lexem_stream.peek().get_token() == Tokens::Token::EXCLAMATION) {
                    lexem_stream.next();
                    instr->add_arg(std::make_shared<UpdatingMemoryAccess>
                                           (std::make_shared<Register>(regstr.get_curr_lexem()),
                                            std::make_shared<ImmediateValue>(offset.get_curr_lexem())));

                } else {
                    instr->add_arg(std::make_shared<MemoryAccess>
                                           (std::make_shared<Register>(regstr.get_curr_lexem()),
                                            std::make_shared<ImmediateValue>(offset.get_curr_lexem())));

                }

            }
        }

        void Parser::parse_bl(const std::shared_ptr<Instruction>& instr) {
            auto val = lexem_stream.next();
            if (program->has_function_definition(val.get_curr_lexem())) {
                instr->add_arg(program->get_function(val.get_curr_lexem()));
            } else {
                instr->add_arg(std::make_shared<Function>(val.get_curr_lexem()));
            }
        }

        void Parser::parse_store(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(reg.get_curr_lexem()));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            assert(val.get_token() == Tokens::Token::L_BRACKET)
            auto regstr = lexem_stream.next();
            assert(Tokens::registers_map.contains(regstr.get_curr_lexem()))
            auto nxt = lexem_stream.next();
            if (nxt.get_token() == Tokens::Token::R_BRACKET) {
                instr->add_arg(std::make_shared<MemoryAccess>
                                       (std::make_shared<Register>(regstr.get_curr_lexem()),
                                        std::make_shared<ImmediateValue>("0")));
                nxt = lexem_stream.next();
                assert(nxt.get_token() == Tokens::Token::COMMA)
                nxt = lexem_stream.next();
                assert(nxt.get_token() == Tokens::Token::DEC_NUMBER)
                instr->add_arg(std::make_shared<ImmediateValue>(nxt.get_curr_lexem()));
            } else {
                assert(nxt.get_token() == Tokens::Token::COMMA)
                auto offset = lexem_stream.next();
                assert(offset.get_token() == Tokens::Token::DEC_NUMBER)
                assert(lexem_stream.next().get_token() == Tokens::Token::R_BRACKET)
                instr->add_arg(std::make_shared<MemoryAccess>
                                       (std::make_shared<Register>(regstr.get_curr_lexem()),
                                        std::make_shared<ImmediateValue>(offset.get_curr_lexem())));
            }
        }

        void Parser::parse_compare(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(reg.get_curr_lexem()));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            if (Tokens::registers_map.contains(val.get_curr_lexem())) {
                instr->add_arg(std::make_shared<Register>(val.get_curr_lexem()));
            } else if (val.get_token() == Tokens::Token::DEC_NUMBER) {
                instr->add_arg(std::make_shared<ImmediateValue>(val.get_curr_lexem()));
            } else ERROR(val, "Expected register or immediate value");
        }

        void Parser::parse_branch(const std::shared_ptr<Instruction>& instr) {
            handle_condition_code(instr);
            auto val = lexem_stream.next();
            assert(val.get_token() == Tokens::Token::LABEL)
            instr->add_arg(std::make_shared<Label>(val.get_curr_lexem()));
        }

        void Parser::handle_condition_code(const std::shared_ptr<Instruction>& instr) {
            // get last two characters of instruction name
            if (instr->get_name().length() < 3) return;
            auto cond_code = instr->get_name().substr(instr->get_name().size() - 2);
            if (cond_code == "eq") {
                instr->set_condition(ConditionCode::EQ);
            } else if (cond_code == "ne") {
                instr->set_condition(ConditionCode::NE);
            } else if (cond_code == "cs") {
                instr->set_condition(ConditionCode::CS);
            } else if (cond_code == "hs") {
                instr->set_condition(ConditionCode::HS);
            } else if (cond_code == "cc") {
                instr->set_condition(ConditionCode::CC);
            } else if (cond_code == "lo") {
                instr->set_condition(ConditionCode::LO);
            } else if (cond_code == "mi") {
                instr->set_condition(ConditionCode::MI);
            } else if (cond_code == "pl") {
                instr->set_condition(ConditionCode::PL);
            } else if (cond_code == "vs") {
                instr->set_condition(ConditionCode::VS);
            } else if (cond_code == "vc") {
                instr->set_condition(ConditionCode::VC);
            } else if (cond_code == "hi") {
                instr->set_condition(ConditionCode::HI);
            } else if (cond_code == "ls") {
                instr->set_condition(ConditionCode::LS);
            } else if (cond_code == "ge") {
                instr->set_condition(ConditionCode::GE);
            } else if (cond_code == "lt") {
                instr->set_condition(ConditionCode::LT);
            } else if (cond_code == "gt") {
                instr->set_condition(ConditionCode::GT);
            } else if (cond_code == "le") {
                instr->set_condition(ConditionCode::LE);
            } else if (cond_code == "al") {
                instr->set_condition(ConditionCode::AL);
            }
        }

        void Parser::parse_adrp(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(reg.get_curr_lexem()));
            assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            assert(val.get_token() == Tokens::Token::LABEL)
            instr->add_arg(std::make_shared<Label>(val.get_curr_lexem()));
        }

        void Parser::parse_cvt(const std::shared_ptr<Instruction>& instr) {
            auto reg = lexem_stream.next();
            assert(Tokens::registers_map.contains(reg.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(reg.get_curr_lexem()));
            asserteq(lexem_stream.next().get_token(), Tokens::Token::COMMA)
            auto val = lexem_stream.next();
            assert(Tokens::registers_map.contains(val.get_curr_lexem()))
            instr->add_arg(std::make_shared<Register>(val.get_curr_lexem()));
        }

        void Parser::handle_instruction(const std::string &ref_name) {
            auto instruction = lexem_stream.next();
            std::shared_ptr<Instruction> instr;

            assert(Tokens::instructions_map.contains(instruction.get_curr_lexem()))
            switch (instruction.get_token()) {
                case Tokens::Token::ADD_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::ADD, instruction.get_curr_lexem());
                    parse_arithmetic(instr);
                    break;
                }
                case Tokens::Token::SUB_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::SUB, instruction.get_curr_lexem());
                    parse_arithmetic(instr);
                    break;
                }
                case Tokens::Token::MUL_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::MUL, instruction.get_curr_lexem());
                    parse_arithmetic(instr);
                    break;
                }
                case Tokens::Token::DIV_OPCODE: {
                    ERROR(instruction, "DIV instruction not implemented yet");
                    instr = std::make_shared<Instruction>(InstructionType::DIV, instruction.get_curr_lexem());
                    break;
                }
                case Tokens::Token::MOVE_INSTRUCTION: {
                    instr = std::make_shared<Instruction>(InstructionType::MOV, instruction.get_curr_lexem());
                    parse_mov(instr);
                    break;
                }
                case Tokens::Token::LOAD_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::LDR, instruction.get_curr_lexem());
                    parse_load(instr);
                    break;
                }
                case Tokens::Token::STORE_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::STR, instruction.get_curr_lexem());
                    parse_store(instr);
                    break;
                }
                case Tokens::Token::BRANCH_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::B, instruction.get_curr_lexem());
                    parse_branch(instr);
                    break;
                }
                case Tokens::Token::BRANCH_LINK_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::BL, instruction.get_curr_lexem());
                    parse_bl(instr);
                    break;
                }
                case Tokens::Token::FLOAT_CONVERT: {
                    instr = std::make_shared<Instruction>(InstructionType::CVT, instruction.get_curr_lexem());
                    parse_cvt(instr);
                    break;
                }
                case Tokens::Token::STORE_PAIR_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::STP, instruction.get_curr_lexem());
                    parse_pair_instruction(instr);
                    break;
                }
                case Tokens::Token::LOAD_PAIR_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::LDP, instruction.get_curr_lexem());
                    parse_pair_instruction(instr);
                    break;
                }
                case Tokens::Token::NO_OP_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::NOP, instruction.get_curr_lexem());
                    break;
                }
                case Tokens::Token::RET: {
                    instr = std::make_shared<Instruction>(InstructionType::RET, instruction.get_curr_lexem());
                    break;
                }
                case Tokens::Token::COMPARE_OPCODE: {
                    instr = std::make_shared<Instruction>(InstructionType::CMP, instruction.get_curr_lexem());
                    parse_compare(instr);
                    break;
                }
                case Tokens::Token::PC_RELATIVE_ADR_CALC: {
                    instr = std::make_shared<Instruction>(InstructionType::ADRP, instruction.get_curr_lexem());
                    parse_adrp(instr);
                    break;
                }
                case Tokens::Token::LOAD_REGISTER_SIGNED_BYTE: {
                    instr = std::make_shared<Instruction>(InstructionType::LDR_SIGNED, instruction.get_curr_lexem());
                    parse_load(instr);
                    break;
                }
                case Tokens::Token::LOAD_REGISTER_BYTE: {
                    instr = std::make_shared<Instruction>(InstructionType::LDR, instruction.get_curr_lexem());
                    parse_load(instr);
                    break;
                }
                case Tokens::Token::LOAD_REGISTER_HW: {
                    instr = std::make_shared<Instruction>(InstructionType::LDR, instruction.get_curr_lexem());
                    parse_load(instr);
                    break;
                }
                case Tokens::Token::LOAD_REGISTER_SIGNED_HW: {
                    instr = std::make_shared<Instruction>(InstructionType::LDR_SIGNED, instruction.get_curr_lexem());
                    parse_load(instr);
                    break;
                }
                case Tokens::Token::LOAD_REGISTER_SIGHED_WORD: {
                    instr = std::make_shared<Instruction>(InstructionType::LDR_SIGNED, instruction.get_curr_lexem());
                    parse_load(instr);
                    break;
                }
                case Tokens::Token::FLOAT_MOVE_INSTRUCTION: {
                    instr = std::make_shared<Instruction>(InstructionType::MOV, instruction.get_curr_lexem());
                    parse_mov(instr);
                    break;
                }

                default:
                    ERROR(instruction, "Expected a supported instruction");
            }
            program->get_function(ref_name)->add_instruction(instr);
        }

        void Parser::handle_cfi(const std::string &ref_name) {
            auto cfi = lexem_stream.next();
            assert(Tokens::cfi_map.contains(cfi.get_curr_lexem()))
            std::shared_ptr<Instruction> instr;
            switch (cfi.get_token()) {
                case Tokens::Token::CFI_DEF_CFA_OFFSET: {
                    auto offset = lexem_stream.next();
                    assert(offset.get_token() == Tokens::Token::DEC_NUMBER)
                    instr = std::make_shared<Instruction>(InstructionType::CFI_CFA, cfi.get_curr_lexem());
                    instr->add_arg(std::make_unique<ImmediateValue>(offset.get_curr_lexem()));
                    break;
                }
                case Tokens::Token::CFI_OFFSET: {
                    auto reg = lexem_stream.next();
                    assert(lexem_stream.next().get_token() == Tokens::Token::COMMA)
                    auto offset = lexem_stream.next();
                    assert(offset.get_token() == Tokens::Token::DEC_NUMBER)
                    instr = std::make_shared<Instruction>(InstructionType::CFI_OFFSET, cfi.get_curr_lexem());
                    instr->add_arg(std::make_shared<Register>("r" + reg.get_curr_lexem()));
                    instr->add_arg(std::make_shared<ImmediateValue>(offset.get_curr_lexem()));
                    break;
                }
                case Tokens::Token::CFI_RESTORE: {
                    auto reg = lexem_stream.next();
                    instr = std::make_shared<Instruction>(InstructionType::CFI_RESET, cfi.get_curr_lexem());
                    instr->add_arg(std::make_shared<Register>("r" + reg.get_curr_lexem()));
                    break;
                }
                case Tokens::Token::CFI_ENDPROC: {
                    instr = std::make_shared<Instruction>(InstructionType::CFI_END, cfi.get_curr_lexem());
                    break;
                }
                default:
                    ERROR(lexem_stream.previous(), "Expected a supported CFI");
            }
            program->get_function(ref_name)->add_instruction(instr);
        }

        void Parser::assign_instructions(const std::string &ref_name) {
            auto func = program->get_function(ref_name);
            if (func == nullptr) ERROR(lexem_stream.current(), "Function not found");
            if (lexem_stream.peek().get_token() == Tokens::Token::CFI_STARTPROC) {
                auto cfisp = lexem_stream.next();
                program->get_function(ref_name)->add_instruction(std::make_shared<Instruction>(InstructionType::CFI_START, cfisp.get_curr_lexem()));
                assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
            }
            while (lexem_stream.peek().get_token() != Tokens::Token::FUNC_END_LABEL) {
                if (Tokens::instructions_map.contains(lexem_stream.peek().get_curr_lexem())) {
                    handle_instruction(ref_name);
                } else if (Tokens::cfi_map.contains(lexem_stream.peek().get_curr_lexem())) {
                    handle_cfi(ref_name);
                } else if (lexem_stream.peek().get_token() == Tokens::Token::LABEL) {
                    program->get_function(ref_name)->add_instruction(std::make_shared<Instruction>(InstructionType::LABEL,
                                                                                                 lexem_stream.next().get_curr_lexem()));
                } else {
                    ERROR(lexem_stream.current(), "Expected a supported instruction");
                }

                if (lexem_stream.next().get_token() != Tokens::Token::EOL_TOKEN) {
                    ERROR(lexem_stream.previous(), "Expected EOL");
                }
            }
            assert(lexem_stream.next().get_token() == Tokens::Token::FUNC_END_LABEL)
            assert(lexem_stream.next().get_token() == Tokens::Token::EOL_TOKEN)
        }

        void Parser::add_variable(const std::shared_ptr<Variable> &var) {
            if (program->get_variable(var->get_name()) != nullptr) {
                ERROR(lexem_stream.previous(), "Variable already defined");
            }
            program->add_variable(var);
        }
    }
#undef assert
