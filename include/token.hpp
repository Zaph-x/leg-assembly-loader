#ifndef ARM_TOKENS_HPP
#define ARM_TOKENS_HPP

#include <string>
#include <stdio.h>
#include <unordered_map>
namespace ARM{
namespace Tokens{

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
  X(EOL_TOKEN)     \
  X(MINUS_SIGN)    \
  X(EXCLAMATION)

#define ARITHMATIC_OPS \
  X(ADD)\
  X(ADC)\
  X(QADD)\
  X(SUB)\
  X(SBC)\
  X(RSB)\
  X(QSUB)\
  X(MUL)\
  X(MLA)\
  X(MLS)\
  X(UMULL)\
    



#define OPCODES \
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
    X(RET)

#define REGISTERS \
  X(_64BIT_REGISTER) \
  X(_32BIT_REGISTER) \
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
  X(LR)

#define LABELS \
X(ARCHITECTURE)\
X(CPU) \
X(INCLUDE_ASM_FILE) \
X(GLOBAL) \
X(SIZE) \
X(FILE)\
X(TEXT)\
X(SECTION)\
X(AlIGN)\
X(IDENTIFIER)

#define SECTIONS \
X(DATA) \
X(READ_ONLY_DATA) \
X(TEXT) \
X(UNINITIALISED) \
X(READ_ONLY_DATA)


#define DATATYPES \
STRING_TYPES \
X(BYTE) \
X(HWORD) \
X(_2BYTE) \
X(WORD) \
X(_4BYTE) \
X(QUAD) \
X(_8BYTE) \
X(XWORD)

#define STRING_TYPES \
X(ASCII) \
X(ASCIIZ) \
X(STRING) \
X(STRING8) \
X(STRING16)

#define SECTION_FLAGS \
X(ALLOCATABLE) \
X(EXECUTABLE) \
X(WRITABLE) \
X(HAS_NULL_TERMINATED_STRINGS)

#define CONSTANTS \
X(STRING)\
X(ALIGN)\
X(SECTION_LOCATION)\
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

#define TOKENS \
    SYMBOLS \
    OPCODES\
    DATATYPES\
    REGISTERS\
    LABELS\
    KEYWORDS\
    CONSTANTS \
    SECTION_FLAGS

enum class Token {
#define X(OP) OP,
TOKENS
#undef X
};

inline std::ostream& operator<<(std::ostream& os, const Token& c) {
  switch (c) {
#define X(OP)     \
  case Token::OP: \
    return os << #OP;
    TOKENS
#undef X
  default:
    return os << "Unknown";
  }
};


inline static std::unordered_map<std::string, Token> keywords = {
  {".align",Token::ALIGN},
  {".file", Token::FILE},
  {".arch", Token::ARCHITECTURE},
  {".text", Token::TEXT}
};

inline static std::unordered_map<char, Token> symbols_map = {
  {EOF, Token::EOF_TOKEN},
  {'[', Token::L_BRACKET},
  {']', Token::R_BRACKET},
  {'-', Token::MINUS_SIGN},
  {'!', Token::EXCLAMATION}
};

inline static std::unordered_map<char, Token> section_flags_map = {
  {'a', Token::ALLOCATABLE},
  {'x', Token::EXECUTABLE},
  {'w', Token::WRITABLE},
  {'s', Token::HAS_NULL_TERMINATED_STRINGS}
};
 
inline static std::unordered_map<std::string, Token> register_map = {
  {"w", Token::_32BIT_REGISTER},
  {"x", Token::_64BIT_REGISTER},
  {"sp", Token::SP},
  {"zr", Token::ZR},
  {"wzr", Token::WZR},
  {"xzr", Token::XZR},
  {"pc", Token::PC},
  {"elr", Token::ELR},
  {"elr_el1", Token::ELR_EL1},
  {"elr_el2", Token::ELR_EL2},
  {"elr_el3", Token::ELR_EL3},
  {"spsr_el1", Token::SPSR_EL1},
  {"spsr_el2", Token::SPSR_EL2},
  {"spsr_el3", Token::SPSR_EL3},
  {"spsr", Token::SPSR},
  {"cpsr", Token::CPSR},
  {"fp", Token::FP},
  {"lr", Token::LR},
};

inline static std::unordered_map<std::string, Token>datatype_map = {
  {"ascii", Token::ASCII},
  {"asciiz", Token::ASCIIZ},
  {"string", Token::STRING},
  {"string8", Token::STRING8},
  {"string16", Token::STRING16},
  {"byte", Token::BYTE},
  {"hword", Token::HWORD},
  {"_2byte", Token::_2BYTE},
  {"word", Token::WORD},
  {"_4byte", Token::_4BYTE},
  {"quad", Token::QUAD},
  {"_8byte", Token::_8BYTE},
  {"xword", Token::XWORD},
};

// X(_8BYTE) \
// X(XWORD)
} //End of namespace Tokens
} //End of namespace ARM

#endif

//   .arch armv8-a
//   .file	"constants.c"
//   .text
//   .global	a
//   .data
//   .align	2
//   .type	a, %object
//   .size	a, 4
// a:
//   .word	12
//   .global	b
//   .align	3
//   .type	b, %object
//   .size	b, 8
// b:
//   .xword	1234567890
//   .global	c
//   .type	c, %object
//   .size	c, 1
// c:
//   .byte	97
//   .global	d
//   .align	2
//   .type	d, %object
//   .size	d, 4
// d:
//   .word	1067320914
//   .global	e
//   .align	3
//   .type	e, %object
//   .size	e, 8
// e:
//   .word	1115938331
//   .word	1072939210
//   .global	f
//   .section	.rodata
//   .align	3
// .LC0:
//   .string	"Hello, World!"
//   .section	.data.rel.local,"aw"
//   .align	3
//   .type	f, %object
//   .size	f, 8
// f:
//   .xword	.LC0
//   .section	.rodata
//   .align	3
// .LC1:
//   .string	"%d"
//   .align	3
// .LC2:
//   .string	"%ld"
//   .align	3
// .LC3:
//   .string	"%f"
//   .align	3
// .LC4:
//   .string	"%lf"
//   .align	3
// .LC5:
//   .string	"%s"
//   .text
//   .align	2
//   .global	main
//   .type	main, %function
// main:
// .LFB0:
//   .cfi_startproc
//   stp	x29, x30, [sp, -16]!
//   .cfi_def_cfa_offset 16
//   .cfi_offset 29, -16
//   .cfi_offset 30, -8
//   mov	x29, sp
//   adrp	x0, a
//   add	x0, x0, :lo12:a
//   ldr	w0, [x0]
//   mov	w1, w0
//   adrp	x0, .LC1
//   add	x0, x0, :lo12:.LC1
//   bl	printf
//   adrp	x0, b
//   add	x0, x0, :lo12:b
//   ldr	x0, [x0]
//   mov	x1, x0
//   adrp	x0, .LC2
//   add	x0, x0, :lo12:.LC2
//   bl	printf
//   adrp	x0, c
//   add	x0, x0, :lo12:c
//   ldrb	w0, [x0]
//   bl	putchar
//   adrp	x0, d
//   add	x0, x0, :lo12:d
//   ldr	s0, [x0]
//   fcvt	d0, s0
//   adrp	x0, .LC3
//   add	x0, x0, :lo12:.LC3
//   bl	printf
//   adrp	x0, e
//   add	x0, x0, :lo12:e
//   ldr	d0, [x0]
//   adrp	x0, .LC4
//   add	x0, x0, :lo12:.LC4
//   bl	printf
//   adrp	x0, f
//   add	x0, x0, :lo12:f
//   ldr	x0, [x0]
//   mov	x1, x0
//   adrp	x0, .LC5
//   add	x0, x0, :lo12:.LC5
//   bl	printf
//   mov	w0, 0
//   ldp	x29, x30, [sp], 16
//   .cfi_restore 30
//   .cfi_restore 29
//   .cfi_def_cfa_offset 0
//   ret
//   .cfi_endproc
// .LFE0:
//   .size	main, .-main
//   .ident	"GCC: (Debian 8.3.0-6) 8.3.0"
//   .section	.note.GNU-stack,"",@progbits
