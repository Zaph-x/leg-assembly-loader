namespace ARM_TOKENS{
    //stp x29, x30, (sp, -48)!

#include <unordered_map>

#define TOKENS \
    INSTRUCTIONS\
    REGISTERS\
    HEADER\
    KEYWORDS\
    CONSTANTS\
    MODIFIERS

    enum class Token {
#define X(OP) OP,
        TOKENS
#undef X
    };

#define INSTRUCTIONS \
    X(STP)\
    X(STR)\
    X(LDP)\
    X(LDR)\
    X(ADD)\
    X(ADC)\
    X(QADD)\
    X(SUB)\
    X(MUL)\
    X(DIV)\
    X(MOV)\
    X(B)\
    X(BL)\
    X(BEQ)\
    X(BNE)\
    X(BLT)\
    X(BGT)\
    X(BLE)\
    X(BGE)\
    X(CMP)\
    X(CMN)\
    X(TST)\
    X(AND)\
    X(ORR)\
    X(EOR)\
    X(ASR)\
    X(LSL)\
    X(LSR)\
    X(RET) \

#define REGISTERS \
  X(X0) \
  X(X1) \
  X(X2) \
  X(X3) \
  X(X4) \
  X(X5) \
  X(X6) \
  X(X7) \
  X(X8) \
  X(X9) \
  X(X10) \
  X(X11) \
  X(X12) \
  X(X13) \
  X(X14) \
  X(X15) \
  X(X16) \
  X(X17) \
  X(X18) \
  X(X19) \
  X(X20) \
  X(X21) \
  X(X22) \
  X(X23) \
  X(X24) \
  X(X25) \
  X(X26) \
  X(X27) \
  X(X28) \
  X(X29) \
  X(X30) \
  X(W0) \
  X(W1) \
  X(W2) \
  X(W3) \
  X(W4) \
  X(W5) \
  X(W6) \
  X(W7) \
  X(W8) \
  X(W9) \
  X(W10) \
  X(W11) \
  X(W12) \
  X(W13) \
  X(W14) \
  X(W15) \
  X(W16) \
  X(W17) \
  X(W18) \
  X(W19) \
  X(W20) \
  X(W21) \
  X(W22) \
  X(W23) \
  X(W24) \
  X(W25) \
  X(W26) \
  X(W27) \
  X(W28) \
  X(W29) \
  X(W30) \
  X(SP) \
    X(ZR) \
    X(WZR) \
    X(XZR) \
    X(PC) \
    X(ELR) \
    X(ELR_EL1) \
    X(ELR_EL2) \
    X(ELR_EL3) \
    X(SPSR_EL1) \
    X(SPSR_EL2) \
    X(SPSR_EL3) \
    X(SPSR) \
    X(CPSR) \
    X(FP) \
    X(LR) \

#define HEADER \
X(ARCHITECTURE)\
X(FILE)\
X(TEXT)\
X(SECTION)\
X(AlIGN)\


#define CONSTANTS \
X(STRING)\
X(ALIGN)\
X(SECTION)\
X(TEXT)\
X(TYPE)\
X(GLOBAL)


#define KEYWORDS \
  X(FUNC_BEGIN_LABEL)   \
  X(FUNC_END_LABEL)   \
  X(BLOCK_BEGIN_LABEL)  \
  X(BLOCK_END_LABEL)     \
  X(CFA)         \
  X(ENTRYPOINTS) \
  X(HEAP)        \
  X(INITIALISER)

#define MODIFIERS \
  X(EXCLAMATION) \

#define SYMBOLS    \
  X(EOF_TOKEN)     \
  X(COLON)         \
  X(EQUAL_SIGN)    \
  X(L_BRACKET)     \
  X(R_BRACKET)     \
  X(L_PARA)        \
  X(R_PARA)        \
  X(R_ARROW)       \
  X(DOLLAR_SIGN)   \
  X(LINE_COMMENT)  \
  X(COMMENT_START) \
  X(COMMENT_END)   \
  X(AT_SIGN)       \
  X(EOL_TOKEN)

inline static std::unordered_map<std::string, int> token_map = {
};
}