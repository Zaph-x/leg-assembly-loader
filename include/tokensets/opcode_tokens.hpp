#ifndef OPCODE_TOKENS_HPP
#define OPCODE_TOKENS_HPP


#define OPCODES \
    X(ADD_OPCODE) \
    X(ADD_CARRY_OPCODE)            \
    X(SUB_OPCODE) \
    X(SUB_CARRY_OPCODE) \
    X(REVERSE_SUB_OPCODE) \
    X(REVERSE_SUB_CARRY_OPCODE) \
    X(MUL_OPCODE) \
    X(DIV_OPCODE) \
    X(LOGICAL_OPCODE) \
    X(SHIFT_OPCODE) \
    X(LOAD_OPCODE)      \
    X(STORE_OPCODE)            \
    X(BRANCH_OPCODE)               \
    X(BRANCH_LINK_OPCODE)            \
    X(AND_OPCODE)\
    X(EXCLUSIVE_OR_OPCODE)\
    X(OR_OPCODE)\
    X(BIT_CLEAR_OPCODE) \
    X(RET)      \
    X(FLOAT_CONVERT)               \
    X(COMPARE_OPCODE)            \
    X(LOAD_PAIR_OPCODE)            \
    X(STORE_PAIR_OPCODE)            \
    X(PC_RELATIVE_ADR_CALC)            \
    X(LOAD_REGISTER_BYTE)            \
    X(NO_OP_OPCODE)


#endif