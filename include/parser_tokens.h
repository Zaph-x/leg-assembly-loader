#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace ARM {

    enum ConditionCode {
        NONE, EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL
    };

    enum ShiftType {
        LSL, LSR, ASR, ROR, RRX
    };



    class Token {
    protected:
        Token(std::string, int, int) {};
        virtual ~Token() {};

        int get_line() { return line; }
        int get_column() { return position; }
        Token() = default;
        int line;
        int position;
        std::string lexem;
    public:
        std::string get_value() { return lexem; }
    };

    class InstructionToken : public Token {
    protected:
        InstructionToken() = default;
        InstructionToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~InstructionToken() = default;
        ConditionCode get_condition_code() const { return condition; }

        ConditionCode condition;
    };

    class StringToken : public Token {
    public:
        StringToken() = default;
        StringToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~StringToken() = default;
    };
    class ArithmeticInstructionToken : public InstructionToken {
    public:
        ArithmeticInstructionToken() = default;
        ArithmeticInstructionToken(std::string lexem, int line, int position, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
        }
        ~ArithmeticInstructionToken() = default;
    };


    class LogicalInstructionToken : public InstructionToken {
    public:
        LogicalInstructionToken() = default;
        LogicalInstructionToken(std::string lexem, int line, int position, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
        }
        ~LogicalInstructionToken() = default;
    };

    class BranchInstructionToken : public InstructionToken {
    public:
        BranchInstructionToken() = default;
        BranchInstructionToken(std::string lexem, int line, int position, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
        }
        ~BranchInstructionToken() = default;
    };

    class MoveInstructionToken : public InstructionToken {
    public:
        MoveInstructionToken() = default;
        MoveInstructionToken(std::string lexem, int line, int position, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
        }
        ~MoveInstructionToken() = default;
    };

    class ShiftInstructionToken : public InstructionToken {
    public:
        ShiftInstructionToken() = default;
        ShiftInstructionToken(std::string lexem, int line, int position, ShiftType shift_type, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
            shift = shift_type;
        }
        ~ShiftInstructionToken() = default;
    private:
        ShiftType shift;
    };

    class StoreInstructionToken : public InstructionToken {
    public:
        StoreInstructionToken() = default;
        StoreInstructionToken(std::string lexem, int line, int position, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
        }
        ~StoreInstructionToken() = default;
    };

    class LoadInstructionToken : public InstructionToken {
    public:
        LoadInstructionToken() = default;
        LoadInstructionToken(std::string lexem, int line, int position, ConditionCode condition_code = ConditionCode::NONE) : InstructionToken(lexem, line, position) {
            condition = condition_code;
        }
        ~LoadInstructionToken() = default;
    };

    class DatatypeToken : public Token {
    public:
        DatatypeToken() = default;
        DatatypeToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~DatatypeToken() = default;
    };

    class DirectiveToken : public Token {
    public:
        DirectiveToken() = default;
        DirectiveToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~DirectiveToken() = default;
    };

    class RegisterToken : public Token {
    public:
        RegisterToken() = default;
        RegisterToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~RegisterToken() = default;
    private:
        int number;
        char name;
    };

    class LabelToken : public Token {
    public:
        LabelToken() = default;
        LabelToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~LabelToken() = default;
        std::string get_name() const { return name; }
    private:
        std::string name;
    };

    class ImmediateToken : public Token {
    public:
        ImmediateToken() = default;
        ImmediateToken(std::string lexem, int line, int position) : Token(lexem, line, position) {}
        ~ImmediateToken() = default;
        int get_value() const { return value; }
    private:
        int value;
    };
}

#endif // TOKENS_HPP