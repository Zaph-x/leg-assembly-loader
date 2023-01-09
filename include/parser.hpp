#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <iomanip>
#include "token.hpp"
#include "lexer.hpp"
#include "converter.hpp"


namespace ARM{
namespace Parser{

    enum class GlobalType {
        UNDEFINED, F, O, T, REF
    };

    class Node {
    public:
        Node() = default;
        virtual ~Node() = default;
        virtual void print() = 0;
        virtual void add_node(std::shared_ptr<Node> node) = 0;
    };

    inline std::string to_string(const Node &node) {
        std::stringstream ss;
        ss << typeid(node).name();
        return ss.str();
    }


    class DefinitionStub : public Node {

    public:
        DefinitionStub() = default;
        explicit DefinitionStub(const std::string &name) {
            this->name = name;
            this->type = GlobalType::UNDEFINED;
        }
        ~DefinitionStub() override = default;

        void print() override { return; }
        void add_node(std::shared_ptr<Node> node) override {return;}
        std::string get_name() const { return name;}
        GlobalType get_type() const { return type;}
        int get_size() const {return size;}
        void set_name(const std::string name) { this->name = name;}
        std::vector<std::string> get_values() const {return values;}
        void add_value(const std::string &value) {values.push_back(value);}
        void set_size(int size) {this->size=size;}
        void set_type(GlobalType type) {this->type=type;}

    private:
        std::string name;
        GlobalType type = GlobalType::UNDEFINED;
        int size{};
        std::vector<std::string> values;

        friend class Variable;
        friend class Function;
    };

    class Register : public Node {
    public:
        Register() = default;
        explicit Register(const std::string &name) {
            this->name = name;
        }
        ~Register() override = default;

        void print() override { return; }
        void add_node( std::shared_ptr<Node>node) override {return;}
        std::string get_name() const { return name;}
    private:
        std::string name;
    };

    class ImmediateValue : public Node {
    public:
        ImmediateValue() = default;
        explicit ImmediateValue(const std::string &value) {
            this->value = value;
        }
        ~ImmediateValue() override = default;

        void print() override { return; }
        void add_node(std::shared_ptr<Node>node) override {return;}
    private:
        std::string value;
    };

    class MemoryAccess : public Node {
    public:
        MemoryAccess() = default;
        explicit MemoryAccess(std::shared_ptr<Register> reg, std::shared_ptr<ImmediateValue> imm) {
            this->reg.swap(reg);
            this->imm.swap(imm);
        }
        ~MemoryAccess() override = default;
        void print() override { return; }
        void add_node(std::shared_ptr<Node>node) override {return;}
    private:
        std::shared_ptr<Register> reg{};
        std::shared_ptr<ImmediateValue> imm{};
    };

    class UpdatingMemoryAccess : public MemoryAccess {
    public:
        explicit UpdatingMemoryAccess(std::shared_ptr<Register> reg, std::shared_ptr<ImmediateValue> imm) : MemoryAccess(std::move(reg), std::move(imm)) {};
    };

    enum class InstructionType {
        ADD, SUB, MUL, DIV, MOV, CMP, B, BL, LDR, STR, CVT, STP, LDP, RET, CFI_CFA, CFI_OFFSET, CFI_RESET, UNDEFINED,
        NOP, LABEL, ADRP, LDR_SIGNED, CFI_START, CFI_END
    };

    enum class ConditionCode {
        EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL, HS, LO
    };

    class Instruction : public Node {
    public:
        Instruction() = default;
        explicit Instruction(InstructionType type, const std::string &name) {
            this->type = type;
            this->name = name;
        }
        ~Instruction() override = default;

        void print() override {};
        void add_node(std::shared_ptr<Node> node) override {};
        InstructionType get_type() const { return type;}
        std::string get_name() const { return name;}
        void add_arg(std::shared_ptr<Node> arg) { args.push_back(std::move(arg));}
        std::vector<std::shared_ptr<Node>> get_args() const { return args;}
        void set_condition(ConditionCode condition) { this->cond = condition;}
    private:
        InstructionType type = InstructionType::UNDEFINED;
        ConditionCode cond = ConditionCode::AL;
        std::vector<std::shared_ptr<Node>> args;
        std::string name;
    };

    class Label : public Node {
    public:
        Label() = default;
        explicit Label(const std::string &name) {
            this->name = name;
        }
        ~Label() override = default;

        void print() override { return; }
        void add_node(std::shared_ptr<Node>node) override {return;}
        std::string get_name() const { return name;}
    private:
        std::string name;
    };

    class Variable : public DefinitionStub {
    public:
        Variable() = default;
        Variable(const DefinitionStub &def)
        {
            if (def.type != GlobalType::O and def.type != GlobalType::REF) throw std::runtime_error("Wrong type of definition");
            this->name = def.name;
            this->size = def.size;
            this->values = def.values;
            this->type = def.type;
        }
        ~Variable() override = default;
    };

    enum class CFIType {
        DEF_CFA_OFFSET, DEF_CFA_REGISTER, OFFSET, RESTORE, UNDEFINED
    };

    class CFI : public Node {
    public:
        CFI() = default;
        CFI(CFIType type) {
            this->type = type;
        }
        ~CFI() override = default;
        void print() override { }
        void add_node(std::shared_ptr<Node>node) override {}
        CFIType get_type() const { return type;}
        void set_reg(Register *reg) { this->reg = reg;}
        void set_imm(ImmediateValue *imm) { this->imm = imm;}

    private:
        CFIType type = CFIType::UNDEFINED;
        Register *reg{};
        ImmediateValue *imm{};
    };

    class Function : public DefinitionStub{
    public:
        Function() = default;
        Function(const DefinitionStub &def)
        {
            if (def.type != GlobalType::F) throw std::runtime_error("Wrong type of definition");
            this->name = def.name;
            this->size = def.size;
            this->values = def.values;
            this->type = GlobalType::F;
            is_external = false;
        }
        Function(const std::string &name) {
            this->name = name;
            this->type = GlobalType::F;
            is_external = true;
        }
        ~Function() override = default;

        void print() override { return; }
        void add_node(std::shared_ptr<Node> node) override {return;}
        void add_instruction(const std::shared_ptr<Instruction>& instruction) { instructions.push_back(instruction);}
        std::vector<std::shared_ptr<Instruction>> get_instructions() const { return instructions;}
    private:
        std::vector<std::shared_ptr<Instruction>> instructions;
        bool is_external = false;
    };



    class Program : public Node {
    public:
        Program() = default;
        ~Program() = default;
        void print() {
            for (auto &node : nodes) {
                node->print();
            }
        }
        void add_node(std::shared_ptr<Node> node) {
            if (node != nullptr)
            {
                std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(node);
                global_variables.push_back(var);
            }
            nodes.push_back(node);
        }

        void add_variable(const std::shared_ptr<Variable>& var) {
            global_variables.push_back(var);
        }

        std::vector<std::shared_ptr<Variable>> get_global_variables() const { return global_variables;}

        std::shared_ptr<Variable> get_variable(const std::string &name) {
            for (auto &var : global_variables) {
                if (var->get_name() == name) {
                    return var;
                }
            }
            return nullptr;
        }

        void set_architecture(const std::string &arch) {
            architecture = arch;
        }
        std::string get_architecture() const { return architecture; }
        void set_file_name(const std::string &name) {
            this->file_name = name;
        }
        std::string get_file_name() const { return file_name; }

        bool has_variable_definition(const std::string &identifier){
            return std::any_of(global_variables.begin(), global_variables.end(),[&identifier](std::shared_ptr<Variable> &var) {return var->get_name() == identifier;});
        }

        void add_function(std::shared_ptr<Function> func) {
            functions.push_back(std::move(func));
        }

        std::shared_ptr<Function> get_function(const std::string &name) {
            for (auto &func : functions) {
                if (func->get_name() == name) return func;
            }
            std::shared_ptr<Function> null_val{};
            return null_val;
        }
        std::vector<std::shared_ptr<Function>> get_functions() {
            return functions;
        }
        bool has_function_definition(const std::string &identifier){

            return std::any_of(functions.begin(), functions.end(),[&identifier](std::shared_ptr<Function> &func) {return func->get_name() == identifier;});
        }

    private:
        std::string architecture = "";
        std::string file_name = "";
        std::vector<std::shared_ptr<Node>> nodes;
        std::vector<std::shared_ptr<Variable>> global_variables;
        std::vector<std::shared_ptr<Function>> functions;
    };

    class Directive : public Node {
    public:
        Directive() = default;
        ~Directive() = default;
        void print() {
            std::cout << "Directive: " << directive << std::endl;
        }
        void add_node(Node* node) {
            std::cout << "Error: Cannot add node to directive" << std::endl;
        }
        void set_directive(std::string directive) {
            this->directive = directive;
        }
    private:
        std::string directive;
    };

    enum class Section {
        Text, Data, Bss, RoData, Unknown
    };

    class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        void set_up(const std::string &path);
        void set_up(ARM::Lexer::Lexer &lexer);
        std::shared_ptr<Program> get_program() { return program; }
        void set_program(std::shared_ptr<Program> prg) { this->program = prg; }
        void assign_program();
        void assign_architecture();
        void assign_file_name();
        void nodeify();
        ARM::VectorStream::vector_stream<ARM::Lexer::Lexem> lexem_stream;
        void assign_global();

    private:
        std::shared_ptr<Lexer::Lexer> lexer;
        std::shared_ptr<Program> program;

        void error(int line, const Lexer::Lexem &lxm, const std::string &msg);
        void assign_text_section();

        void verify_stub(const std::string &stub_name);

        bool has_identifier(const std::string &name);

        void assign_global_size();

        void assign_type();

        void handle_label();

        void assign_value(const std::string &ref_name);
        void assign_value(int expected_size, Tokens::Token expected_type, const std::string &ref_name);

        void handle_function(const std::string &ref_name);

        void handle_multi_word(const std::string &ref_name);


        void verify_function_stub(const DefinitionStub &stub);

        void assign_instructions(const std::string &ref_name);

        void handle_instruction(const std::string &ref_name);

        void parse_arithmetic(const std::shared_ptr<Instruction>&instr);

        void parse_mov(const std::shared_ptr<Instruction>&instr);

        void parse_store_load(const std::shared_ptr<Instruction>&instr);

        void parse_pair_instruction(const std::shared_ptr<Instruction>&instr);

        void handle_cfi(const std::string &ref_name);

        void parse_bl(const std::shared_ptr<Instruction>&instr);

        void parse_compare(const std::shared_ptr<Instruction>&instr);

        void parse_branch(const std::shared_ptr<Instruction>&instr);

        void parse_ldp(std::shared_ptr<Instruction> instr);

        void handle_condition_code(const std::shared_ptr<Instruction> &instr);

        void parse_adrp(const std::shared_ptr<Instruction> &instr);

        void parse_cvt(const std::shared_ptr<Instruction> &instr);

        void add_variable(const std::shared_ptr<Variable> &var);
    };
}
}
