#ifndef OPCODE_TOKENS_HPP
#define OPCODE_TOKENS_HPP

#define MOVE_OPS \
    X(MOV)
    
#define SHIFT_OPS \
    X(LSL)\
    X(LSR)\
    X(ASR)\
    X(ROR)\
    X(RRX)
  
  #define CONDITIONL_BRANCH_OPS \
    X(CBZ) \
    X(CBNZ) \
    X(TBNZ) \
    X(BEQ) \
    X(BNE) \
    X(BLT) \
    X(BGT) \
    X(BLE) \
    X(BGE)

#define BRANCH_OPS \
    CONDITIONL_BRANCH_OPS \
    X(B) \
    X(BL) \
    X(BR) \
    X(BLR) \
    X(BX) \
    X(BLX) \
    X(BXJ) \
    X(BLXJ) \
    X(BKPT) \
    X(SVC) \
    X(HVC) \
    X(SMC) \
    X(UDF)

#define FLAG_OPS \
    X(N) \
    X(Z) \
    X(C) \
    X(V) \
    X(Q)

#define OPCODES \
    ARITHMETIC_OPS \
    LOGICAL_OPS \
    MOVE_OPS \
    SHIFT_OPS \
    LOAD_STORE_OPS \
    BRANCH_OPS \
    X(RET)

#endif