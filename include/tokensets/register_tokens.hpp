#ifndef REGISTER_TOKENS_HPP
#define REGISTER_TOKENS_HPP

#define REG(LETTER) \
    X(LETTER##0) \
    X(LETTER##1) \
    X(LETTER##2) \
    X(LETTER##3) \
    X(LETTER##4) \
    X(LETTER##5) \
    X(LETTER##6) \
    X(LETTER##7) \
    X(LETTER##8) \
    X(LETTER##9) \
    X(LETTER##10) \
    X(LETTER##11) \
    X(LETTER##12) \
    X(LETTER##13) \
    X(LETTER##14) \
    X(LETTER##15) \
    X(LETTER##16) \
    X(LETTER##17) \
    X(LETTER##18) \
    X(LETTER##19) \
    X(LETTER##20) \
    X(LETTER##21) \
    X(LETTER##22) \
    X(LETTER##23) \
    X(LETTER##24) \
    X(LETTER##25) \
    X(LETTER##26) \
    X(LETTER##27) \
    X(LETTER##28) \
    X(LETTER##29) \
    X(LETTER##30) \
    X(LETTER##31)

#define _32BIT_REGISTERS \
    REG(W) \
    X(WZR) \
    X(WSP) \

#define _64BIT_REGISTERS \
    REG(X) \
    X(XZR) \
    X(SP) \
    X(PC) \

#define EXCEPTION_LINK_REGISTERS \
    X(SP_EL) \
    X(SP_EL0) \
    X(SP_EL1) \
    X(SP_EL2) \
    X(SP_EL3) \
    X(ELR) \
    X(ELR_EL1) \
    X(ELR_EL2) \
    X(ELR_EL3) \
    X(SPSR) \
    X(SPSR_EL1) \
    X(SPSR_EL2) \
    X(SPSR_EL3)

#define SIMD_VECTOR_REGISTERS \
    REG(V)

#define SIMD_FLOAT64_REGISTERS \
    REG(D)

#define SIMD_FLOAT32_REGISTERS \
    REG(S)

#define SIMD_FLOAT16_REGISTERS \
    REG(H) 

#define SIMD_FLOAT8_REGISTERS \
    REG(B)


#define REGISTERS \
    _64BIT_REGISTERS \
    _32BIT_REGISTERS \
    EXCEPTION_LINK_REGISTERS \
    SIMD_VECTOR_REGISTERS \
    SIMD_FLOAT64_REGISTERS \
    SIMD_FLOAT32_REGISTERS \
    SIMD_FLOAT16_REGISTERS \
    SIMD_FLOAT8_REGISTERS \
    X(FP) \
    X(LR)

#endif // REGISTER_TOKENS_HPP