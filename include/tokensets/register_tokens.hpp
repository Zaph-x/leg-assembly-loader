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


#define REGISTERS \
    _64BIT_REGISTERS \
    _32BIT_REGISTERS \
    EXCEPTION_LINK_REGISTERS \
    X(FP) \
    X(LR)

#endif // REGISTER_TOKENS_HPP