#ifndef DATATYPE_TOKENS_HPP
#define DATATYPE_TOKENS_HPP

#define DATATYPE_DEFINITIONS \
    STRING_DATA_DEFINITIONS \
    FLOATING_POINT_DATA_DEFINITION \
    DATA_DEFINITION

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Data-definition-directives
#define DATA_DEFINITION \
    X(BYTE) \
    X(HWORD) \
    X(WORD) \
    X(QUAD) \
    X(OCTA)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/String-definition-directives
#define STRING_DATA_DEFINITIONS \
    X(ASCII) \
    X(ASCIIZ) \
    X(STRING) \
    X(STRING8) \
    X(STRING16)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Floating-point-data-definition-directives
#define FLOATING_POINT_DATA_DEFINITION \
    X(FLOAT) \
    X(DOUBLE)

#endif // DATATYPE_TOKENS_HPP