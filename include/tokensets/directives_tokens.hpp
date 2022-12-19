#ifndef DIRECTIVES_TOKENS_HPP
#define DIRECTIVES_TOKENS_HPP

#include "datatype_tokens.hpp"

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Conditional-assembly-directives
#define CONDITIONAL_ASM_DIRECTIVES \
    X(IF) \
    X(IFNE) \
    X(IFEQ) \
    X(IFGE) \
    X(IFGT) \
    X(IFLE) \
    X(IFLT) \
    X(IFB) \
    X(IFNB) \
    X(IFC) \
    X(IFNC) \
    X(IFEQS) \
    X(IFNES) \
    X(IFDEF) \
    X(IFNDEF) \
    X(ELSEIF) \
    X(ELSE) \
    X(ENDIF)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Symbol-binding-directives
#define SYMBOL_BINDING_DIRECTIVES \
    X(GLOBAL) \
    X(LOCAL) \
    X(WEAK)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Assembly-expressions
#define RELOCATION_SPECIFIERS \
    X(LO12) \
    X(ABS_G3) \
    X(ABS_G2) \
    X(ABS_G2_S) \
    X(ABS_G2_NC) \
    X(ABS_G1) \
    X(ABS_G1_S) \
    X(ABS_G1_NC) \
    X(ABS_G0) \
    X(ABS_G0_S) \
    X(ABS_G0_NC) \
    X(GOT) \
    X(GOT_LO12)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Macro-directives
#define MACRO_DIRECTIVES \
    X(MACRO) \
    X(ENDM) \
    X(EXITM)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Call-Frame-Information-directives
// https://sourceware.org/binutils/docs/as/CFI-directives.html
#define CALL_FRAME_INFORMATION_DIRECTIVES \
    X(CFI_STARTPROC) \
    X(CFI_ENDPROC) \
    X(CFI_SECTIONS)\
    X(CFI_PERSONALITY) \
    X(CFI_PERSONALITY_ID) \
    X(CFI_FDE_DATA) \
    X(CFI_LSDA) \
    X(CFI_INLINE_LSDA) \
    X(CFI_DEF_CFA) \
    X(CFI_DEF_CFA_REGISTER) \
    X(CFI_DEF_CFA_OFFSET) \
    X(CFI_ADJUST_CFA_OFFSET) \
    X(CFI_OFFSET) \
    X(CFI_VAL_OFFSET) \
    X(CFI_REL_OFFSET) \
    X(CFI_REGISTER) \
    X(CFI_RESTORE) \
    X(CFI_REMEMBER_STATE) \
    X(CFI_UNDEFINED) \
    X(CFI_WINDOW_SAVE) \
    X(CFI_ESCAPE) \
    X(CFI_SIGNAL_FRAME) \
    X(CFI_VAL_ENCODED_ADDR) \
    X(CFI_DEBUG_FRAME)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/AArch64-target-selection-directives
#define TARGET_SELECTION_DIRECTIVES \
    X(ARCHITECTURE) \
    X(ARCHITECTURE_EXTENDED) \
    X(CPU)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Space-filling-directives
#define SPACE_FILLING_DIRECTIVES \
    X(FILL) \
    X(SPACE)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Alignment-directives
#define ALIGNMENT_DIRECTIVES \
    X(ALIGN) \
    X(BALIGN) \
    X(BALIGNL) \
    X(BALIGNW) \
    X(P2ALIGN) \
    X(P2ALIGNL) \
    X(P2ALIGNW)

// https://developer.arm.com/documentation/101754/0618/armclang-Reference/armclang-Integrated-Assembler/Section-directives
#define SECTION_DIRECTIVES \
    X(TEXT_SECTION) \
    X(DATA_SECTION) \
    X(RODATA_SECTION) \
    X(BSS_SECTION) \
    X(POPSECTION_SECTION) \
    X(PUSHSECTION_SECTION) \
    X(SECTION)

#define DIRECTIVES \
    TARGET_SELECTION_DIRECTIVES \
    DATATYPE_DEFINITIONS \
    SECTION_DIRECTIVES \
    ALIGNMENT_DIRECTIVES \
    SPACE_FILLING_DIRECTIVES \
    CONDITIONAL_ASM_DIRECTIVES \
    RELOCATION_SPECIFIERS \
    MACRO_DIRECTIVES \
    SYMBOL_BINDING_DIRECTIVES \
    CALL_FRAME_INFORMATION_DIRECTIVES \
    X(INCLUDE_ASM_FILE) \
    X(SIZE) \
    X(FILE)\
    X(TYPE)\
    X(TEXT)        \
    X(COMM)        \
    X(IDENTIFIER)  \
    X(NOTE)

#endif