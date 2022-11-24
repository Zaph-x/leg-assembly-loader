#ifndef ARM_TOKENS_HPP
#define ARM_TOKENS_HPP

#include <string>
#include <iostream>
#include <unordered_map>

#include "tokensets/arithmetic_tokens.hpp"
#include "tokensets/logical_tokens.hpp"
#include "tokensets/store_load_tokens.hpp"
#include "tokensets/directives_tokens.hpp"
#include "tokensets/conditional_tokens.hpp"
#include "tokensets/opcode_tokens.hpp"
#include "tokensets/register_tokens.hpp"

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
    X(EOL_TOKEN)     \
    X(MINUS_SIGN)    \
    X(EXCLAMATION)

#define SECTION_FIELDS \
    SECTION_FLAGS \
    SECTION_TYPES 

#define TYPE_TYPES \
    X(FUNCTION) \
    X(OBJECT) \
    X(TLS_OBJECT)

#define SECTION_FLAGS \
    X(SHF_ALLOC) \
    X(SHF_EXECINSTR) \
    X(SHF_WRITE) \
    X(SHF_STRINGS) \
    X(SHF_ARM_PURECODE) \
    X(SHF_LINK_ORDER) \
    X(SHF_MERGE) \
    X(SHF_TLS) \
    X(SHF_GROUP) \
    X(INHERIT_PREVIOUS_GROUP_IF_PRESENT)

#define SECTION_TYPES \
    X(SHT_PROGBITS)\
    X(SHT_NOBITS)\
    X(SHT_NOTE)\
    X(SHT_INIT_ARRAY)\
    X(SHT_FINI_ARRAY)\
    X(SHT_PREINIT_ARRAY)

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
    REGISTERS\
    DIRECTIVES\
    KEYWORDS\
    SECTION_FIELDS\
    CONDITION_CODES\
    TYPE_TYPES

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

inline static std::unordered_map<std::string, Token> directives_map = {
    {".align",Token::ALIGN},
    {".file", Token::FILE},
    {".arch", Token::ARCHITECTURE},
    {".arch_extended", Token::ARCHITECTURE_EXTENDED},
    {".text", Token::TEXT},
    {".cpu", Token::CPU},
    {".include", Token::INCLUDE_ASM_FILE},
    {".global", Token::GLOBAL},
    {".size", Token::SIZE},
    {".type", Token::TYPE},
    {".space", Token::SPACE},
    {".fill", Token::FILL},
    {".ident", Token::IDENTIFIER}
};

inline static std::unordered_map<char, Token> symbols_map = {
    {EOF, Token::EOF_TOKEN},
    {'[', Token::L_BRACKET},
    {']', Token::R_BRACKET},
    {'-', Token::MINUS_SIGN},
    {'!', Token::EXCLAMATION}
};

inline static std::unordered_map<std::string, Token> branch_map = {
    {"b", Token::B},
    {"bl", Token::BL},
    {"br", Token::BR},
    {"blr", Token::BLR},
    {"bx", Token::BX},
    {"blx", Token::BLX},
    {"bxj", Token::BXJ},
    {"beq", Token::BEQ}, 
    {"bne", Token::BNE}, 
    {"blt", Token::BLT}, 
    {"bgt", Token::BGT}, 
    {"ble", Token::BLE}, 
    {"bge", Token::BGE},
    {"blxj", Token::BLXJ},
    {"bkpt", Token::BKPT},
    {"svc", Token::SVC},
    {"hvc", Token::HVC},
    {"smc", Token::SMC},
    {"udf", Token::UDF},
    {"cbz", Token::CBZ},
    {"cbnz", Token::CBNZ},
    {"tbnz", Token::TBNZ}
};

inline static std::unordered_map<std::string, Token> shift_ops_map = {
    {"lsl", Token::LSL},
    {"lsr", Token::LSR},
    {"asr", Token::ASR},
    {"ror", Token::ROR},
    {"rxx", Token::RRX}
  
};
   

inline static std::unordered_map<char, Token> section_flags_map = {
    {'a', Token::SHF_ALLOC},
    {'w', Token::SHF_WRITE},
    {'y', Token::SHF_ARM_PURECODE},
    {'x', Token::SHF_EXECINSTR},
    {'o', Token::SHF_LINK_ORDER},
    {'M', Token::SHF_MERGE},
    {'S', Token::SHF_STRINGS},
    {'T', Token::SHF_TLS},
    {'G', Token::SHF_GROUP},
    {'?', Token::INHERIT_PREVIOUS_GROUP_IF_PRESENT}
};
// .section .data, "ax", @progbits
inline static std::unordered_map<std::string, Token> section_map = {
    {".data", Token::DATA_SECTION},
    {".rodata", Token::RODATA_SECTION},
    {".text", Token::TEXT_SECTION},
    {".bss", Token::BSS_SECTION},
    {".pushsection", Token::PUSHSECTION_SECTION},
    {".popsection", Token::POPSECTION_SECTION},
    {".section", Token::SECTION}
};


inline static std::unordered_map<std::string, Token> section_types_map = {
    {"%progbits", Token::SHT_PROGBITS},
    {"%nobits", Token::SHT_NOBITS},
    {"%note", Token::SHT_NOTE},
    {"%init_array", Token::SHT_INIT_ARRAY},
    {"%fini_array", Token::SHT_FINI_ARRAY},
    {"%preinit_array", Token::SHT_PREINIT_ARRAY}
};

inline static std::unordered_map<std::string, Token> type_map = {
    {"%function", Token::FUNCTION},
    {"%object", Token::OBJECT},
    {"%tls_object", Token::TLS_OBJECT}
};
 
inline static std::unordered_map<std::string, Token> register_map = {
    /* TODO DEFINE ALL THE REGISTERS */
    {"sp", Token::SP},
    {"zr", Token::XZR},
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
    {"fp", Token::FP},
    {"lr", Token::LR},
};

inline static std::unordered_map<std::string, Token>datatype_map = {
    {".float", Token::FLOAT},
    {".double", Token::DOUBLE},
    {".ascii", Token::ASCII},
    {".asciiz", Token::ASCIIZ},
    {".string", Token::STRING},
    {".string8", Token::STRING8},
    {".string16", Token::STRING16},
    {".byte", Token::BYTE},
    {".1byte", Token::BYTE},
    {".dc.b", Token::BYTE},
    {".hword", Token::HWORD},
    {".2byte", Token::HWORD},
    {".dc", Token::HWORD},
    {".dc.w", Token::HWORD},
    {".short", Token::HWORD},
    {".value", Token::HWORD},
    {".word", Token::WORD},
    {".4bytes", Token::WORD},
    {".long", Token::WORD},
    {".int", Token::WORD},
    {".dc.l", Token::WORD},
    {".quad", Token::QUAD},
    {".8byte", Token::QUAD},
    {".xword", Token::QUAD},
    {".dc.a", Token::QUAD},
    {".octa", Token::OCTA} // This is actually not supported by the assembler yet
};
//Ror har extr som et alias
inline static std::unordered_map<std::string, Token>arithmetic_map = {
    {"add", Token::ADD},
    {"adc", Token::ADC},
    {"qadd", Token::QADD},
    {"sub", Token::SUB},
    {"subs", Token::SUBS},
    {"sub", Token::SUB},
    {"sbc", Token::SBC},
    {"qsub", Token::QSUB},
    {"mul", Token::MUL},
    {"mla", Token::MLA},
    {"mls", Token::MLS},
    {"umull", Token::UMULL},
    {"umlal", Token::UMLAL},
    {"smull", Token::SMULL},
    {"smlal", Token::SMLAL},
    {"udiv", Token::UDIV},
    {"sdiv", Token::SDIV},
};
inline static std::unordered_map<std::string, Token>logical_map = {
    {"and", Token::AND},
    {"orr", Token::ORR},
    {"eor", Token::EOR},
    {"bic", Token::BIC},
    {"eon", Token::EON},
    {"orn", Token::ORN},
    {"teq", Token::TEQ},
    {"teg", Token::TEG},
    {"tst", Token::TST},
    {"cmn", Token::CMN},
    {"cmp", Token::CMP}
};
inline static std::unordered_map<std::string, Token>conditional_map = {
    {"eq", Token::EQ},
    {"ne", Token::NE},
    {"cs", Token::CS},
    {"hs", Token::HS},
    {"cc", Token::CC},
    {"lo", Token::LO},
    {"mi", Token::MI},
    {"pl", Token::PL},
    {"vs", Token::VS},
    {"vc", Token::VC},
    {"hi", Token::HI},
    {"ls", Token::LS},
    {"ge", Token::GE},
    {"lt", Token::LT},
    {"gt", Token::GT},
    {"le", Token::LE},
    {"al", Token::AL},
    {"nv", Token::NV},
};

inline static std::unordered_map<std::string, Token>load_map = {
    {"ldr", Token::LDR},
    {"ldbr", Token::LDRB},
    {"ldrh", Token::LDRH},
    {"ldrw", Token::LDRW},
    {"ldmia", Token::LDMIA},
    {"ldp", Token::LDP},
};
inline static std::unordered_map<std::string, Token>store_map = {
    {"str", Token::STR},
    {"strb", Token::STRB},
    {"strh", Token::STRH},
    {"strw", Token::STRW},
    {"stmia", Token::STMIA},
    {"stp", Token::STP},
};

inline static std::unordered_map<std::string, Token>cfi_map={
    {".cfi_startproc", Token::CFI_STARTPROC},
    {".cfi_endproc", Token::CFI_ENDPROC},
    {".cfi_sections", Token::CFI_SECTIONS},
    {".cfi_personality", Token::CFI_PERSONALITY},
    {".cfi_personality_id", Token::CFI_PERSONALITY_ID},  
    {".cfi_fde_data", Token::CFI_FDE_DATA},
    {".cfi_lsda", Token::CFI_LSDA },
    {".cfi_inline_lsda", Token::CFI_INLINE_LSDA},
    {".cfi_def_cfa", Token::CFI_DEF_CFA},
    {".cfi_def_cfa_register", Token::CFI_DEF_CFA_REGISTER},
    {".cfi_def_cfa_offset", Token::CFI_DEF_CFA_OFFSET},
    {".cfi_adjust_cfa_offset", Token::CFI_ADJUST_CFA_OFFSET},
    {".cfi_offset", Token::CFI_OFFSET},
    {".cfi_val_offset", Token::CFI_VAL_OFFSET},
    {".cfi_rel_offset", Token::CFI_REL_OFFSET},
    {".cfi_register", Token::CFI_REGISTER},
    {".cfi_restore", Token::CFI_RESTORE},
    {".cfi_remember_state", Token::CFI_REMEMBER_STATE},
    {".cfi_undefined", Token::CFI_UNDEFINED},
    {".cfi_window_state", Token::CFI_WINDOW_SAVE},
    {".cfi_escape", Token::CFI_ESCAPE},
    {".cfi_signal_frame", Token::CFI_SIGNAL_FRAME},
    {".cfi_val_encoded_addr", Token::CFI_VAL_ENCODED_ADDR},
    {".cfi_debug_frame", Token::CFI_DEBUG_FRAME}
};
/*
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

 */

} //End of namespace Tokens
} //End of namespace ARM

#endif

//   .arch armv8-a
//   .file	"constants.c"
//   .te{Token::
//},  .global	a
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
