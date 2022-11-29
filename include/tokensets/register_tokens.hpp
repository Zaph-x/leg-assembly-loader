#ifndef REGISTER_TOKENS_HPP
#define REGISTER_TOKENS_HPP

#define _32BIT_REGISTERS \
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
    X(WZR) \
    X(WSP) \

#define _64BIT_REGISTERS \
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
    X(V0) \
    X(V1) \
    X(V2) \
    X(V3) \
    X(V4) \
    X(V5) \
    X(V6) \
    X(V7) \
    X(V8) \
    X(V9) \
    X(V10) \
    X(V11) \
    X(V12) \
    X(V13) \
    X(V14) \
    X(V15) \
    X(V16) \
    X(V17) \
    X(V18) \
    X(V19) \
    X(V20) \
    X(V21) \
    X(V22) \
    X(V23) \
    X(V24) \
    X(V25) \
    X(V26) \
    X(V27) \
    X(V28) \
    X(V29) \
    X(V30) \
    X(V31)

#define SIMD_FLOAT64_REGISTERS \
    X(D0) \
    X(D1) \
    X(D2) \
    X(D3) \
    X(D4) \
    X(D5) \
    X(D6) \
    X(D7) \
    X(D8) \
    X(D9) \
    X(D10) \
    X(D11) \
    X(D12) \
    X(D13) \
    X(D14) \
    X(D15) \
    X(D16) \
    X(D17) \
    X(D18) \
    X(D19) \
    X(D20) \
    X(D21) \
    X(D22) \
    X(D23) \
    X(D24) \
    X(D25) \
    X(D26) \
    X(D27) \
    X(D28) \
    X(D29) \
    X(D30) \
    X(D31)

#define SIMD_FLOAT32_REGISTERS \
    X(S0) \
    X(S1) \
    X(S2) \
    X(S3) \
    X(S4) \
    X(S5) \
    X(S6) \
    X(S7) \
    X(S8) \
    X(S9) \
    X(S10) \
    X(S11) \
    X(S12) \
    X(S13) \
    X(S14) \
    X(S15) \
    X(S16) \
    X(S17) \
    X(S18) \
    X(S19) \
    X(S20) \
    X(S21) \
    X(S22) \
    X(S23) \
    X(S24) \
    X(S25) \
    X(S26) \
    X(S27) \
    X(S28) \
    X(S29) \
    X(S30) \
    X(S31)

#define SIMD_FLOAT16_REGISTERS \
    X(H0) \
    X(H1) \
    X(H2) \
    X(H3) \
    X(H4) \
    X(H5) \
    X(H6) \
    X(H7) \
    X(H8) \
    X(H9) \
    X(H10) \
    X(H11) \
    X(H12) \
    X(H13) \
    X(H14) \
    X(H15) \
    X(H16) \
    X(H17) \
    X(H18) \
    X(H19) \
    X(H20) \
    X(H21) \
    X(H22) \
    X(H23) \
    X(H24) \
    X(H25) \
    X(H26) \
    X(H27) \
    X(H28) \
    X(H29) \
    X(H30) \
    X(H31)

#define SIMD_FLOAT8_REGISTERS \
    X(B0) \
    X(B1) \
    X(B2) \
    X(B3) \
    X(B4) \
    X(B5) \
    X(B6) \
    X(B7) \
    X(B8) \
    X(B9) \
    X(B10) \
    X(B11) \
    X(B12) \
    X(B13) \
    X(B14) \
    X(B15) \
    X(B16) \
    X(B17) \
    X(B18) \
    X(B19) \
    X(B20) \
    X(B21) \
    X(B22) \
    X(B23) \
    X(B24) \
    X(B25) \
    X(B26) \
    X(B27) \
    X(B28) \
    X(B29) \
    X(B30) \
    X(B31)


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