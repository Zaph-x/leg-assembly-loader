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
        UNDEFINED, F, O, T
    };

    class Node {
    public:
        Node() = default;
        virtual ~Node() = default;
        virtual void print() = 0;
        virtual void add_node(Node *node) = 0;
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
        void add_node(Node *node) override {return;}
        std::string get_name() const { return name;}
        GlobalType get_type() const { return type;}
        int get_size() const {return size;}
        std::vector<std::string> get_values() const {return values;}
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

    class Variable : public DefinitionStub {
    public:
        Variable() = default;
        Variable(const DefinitionStub &def)
        {
            if (def.type != GlobalType::O) throw;
            this->name = def.name;
            this->size = def.size;
            this->values = def.values;
            this->type = GlobalType::O;
        }
        ~Variable() override = default;
    };

    class Function : public DefinitionStub{
    public:
        Function() = default;
        Function(const DefinitionStub &def)
        {
            if (def.type != GlobalType::F) throw;
            this->name = def.name;
            this->size = def.size;
            this->values = def.values;
            this->type = GlobalType::F;
        }
        ~Function() override = default;

        /*
        void print() override {
            std::cout << "Function: " << name << std::endl;
            int i = 0;
            for (auto &blcks : blocks) {
                std::cout << "Block " << i << std::endl;
                for (auto &node : blcks) {
                    std::cout << "  Node: " << to_string(*node) << std::endl;
                }
            }
        }
        void add_block(std::vector<Node *> block) {
            blocks.push_back(block);

        }

        void set_name(std::string name) {
            this->name = std::move(name);
        }

    private:
        std::string name;
        std::vector<std::vector<Node *>> blocks;
    };

         */
    };



    class Program : public Node {
    public:
        Program() = default;
        ~Program() = default;
        void print() {
            for (auto node : nodes) {
                node->print();
            }
        }
        void add_node(Node* node) {
            if (dynamic_cast<Variable*>(node) != nullptr)
                global_variables.push_back(dynamic_cast<Variable*>(node));
            nodes.push_back(node);
        }

        void set_architecture(std::string arch) {
            architecture = std::move(arch);
        }
        [[nodiscard]] std::string get_architecture() const { return architecture; }
        void set_file_name(std::string name) {
            this->file_name = std::move(name);
        }
        [[nodiscard]] std::string get_file_name() const { return file_name; }

        bool has_variable_definition(const std::string &identifier){
            std::vector<Variable>::iterator it;

            return std::any_of(global_variables.begin(), global_variables.end(),[&identifier](Variable* var) {return var->get_name() != identifier;});
        }

        bool has_function_definition(const std::string &identifier){
            std::vector<Function>::iterator it;

            return std::any_of(functions.begin(), functions.end(),[&identifier](Function* func) {return func->get_name() != identifier;});
        }

    private:
        std::string architecture;
        std::string file_name;
        std::vector<Node*> nodes;
        std::vector<Variable*> global_variables;
        std::vector<Function*> functions;
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
        Program* get_program() { return &program; }
        void set_program(const Program& prg) { this->program = prg; }
        void assign_program();
        void assign_architecture();
        void assign_file_name();
        void nodeify();
        ARM::VectorStream::vector_stream<ARM::Lexer::Lexem> lexem_stream;
        void assign_global();

    private:
        std::unique_ptr<Lexer::Lexer> lexer;
        Program program;
        void assign_text_section();

        void verify_stub(const std::string &stub_name);

        void parse_object(std::map<std::string, std::string> &placeholder_values);

        bool has_identifier(const std::string &name);

        void assign_global_size();

        void assign_type();

        void handle_label();

        void assign_value(const std::string &ref_name);
        void assign_value(int expected_size, Tokens::Token expected_type, const std::string &ref_name);

        void handle_function();

        void handle_multi_word(const std::string &ref_name);


    };
}
}