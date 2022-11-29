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

namespace ARM
{
    namespace Tokens
    {

#define SYMBOLS      \
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
    X(EXCLAMATION)   \
    X(PLUS_SIGN)     \
    X(COMMA)

#define SECTION_FIELDS \
    SECTION_FLAGS      \
    SECTION_TYPES

#define TYPE_TYPES \
    X(FUNCTION)    \
    X(OBJECT)      \
    X(TLS_OBJECT)

#define SECTION_FLAGS   \
    X(SHF_ALLOC)        \
    X(SHF_EXECINSTR)    \
    X(SHF_WRITE)        \
    X(SHF_STRINGS)      \
    X(SHF_ARM_PURECODE) \
    X(SHF_LINK_ORDER)   \
    X(SHF_MERGE)        \
    X(SHF_TLS)          \
    X(SHF_GROUP)        \
    X(INHERIT_PREVIOUS_GROUP_IF_PRESENT)

#define SECTION_TYPES \
    X(SHT_PROGBITS)   \
    X(SHT_NOBITS)     \
    X(SHT_NOTE)       \
    X(SHT_INIT_ARRAY) \
    X(SHT_FINI_ARRAY) \
    X(SHT_PREINIT_ARRAY)

#define KEYWORDS         \
    X(FUNC_BEGIN_LABEL)  \
    X(FUNC_END_LABEL)    \
    X(BLOCK_BEGIN_LABEL) \
    X(BLOCK_END_LABEL)   \
    X(CFA)               \
    X(ENTRYPOINTS)       \
    X(HEAP)              \
    X(INITIALISER)

#define TOKENS      \
    SYMBOLS         \
    OPCODES         \
    REGISTERS       \
    DIRECTIVES      \
    KEYWORDS        \
    SECTION_FIELDS  \
    CONDITION_CODES \
    TYPE_TYPES \
    X(RAW_STRING) \
    X(DEC_NUMBER)    \
    X(HEX_NUMBER)   \
    X(ERROR)

        enum class Token
        {
#define X(OP) OP,
            TOKENS
#undef X
        };

        inline std::ostream &operator<<(std::ostream &os, const Token &c)
        {
            switch (c)
            {
#define X(OP)       \
    case Token::OP: \
        return os << #OP;
                TOKENS
#undef X
            default:
                return os << "Unknown";
            }
        };

        inline static std::unordered_map<std::string, Token> directives_map = {
            {".alig", Token::ALIGN},
            {".fil", Token::FILE},
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
            {".ident", Token::IDENTIFIER},
            {".if", Token::IF},
            {".ifdef", Token::IFDEF},
            {".ifndef", Token::IFNDEF},
            {".else", Token::ELSE},
            {".endif", Token::ENDIF},
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
            {".octa", Token::OCTA}
        };
            
        inline static std::unordered_map<char, Token> symbols_map = {
            {EOF, Token::EOF_TOKEN},
            {'\n', Token::EOL_TOKEN},
            {'[', Token::L_BRACKET},
            {']', Token::R_BRACKET},
            {'-', Token::MINUS_SIGN},
            {'!', Token::EXCLAMATION},
            {',', Token::COMMA},
            {'+', Token::PLUS_SIGN},
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
            {"tbnz", Token::TBNZ}};

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
            {'?', Token::INHERIT_PREVIOUS_GROUP_IF_PRESENT}};
        // .section .data, "ax", @progbits
        inline static std::unordered_map<std::string, Token> section_map = {
            {".data", Token::DATA_SECTION},
            {".rodata", Token::RODATA_SECTION},
            {".text", Token::TEXT_SECTION},
            {".bss", Token::BSS_SECTION},
            {".pushsection", Token::PUSHSECTION_SECTION},
            {".popsection", Token::POPSECTION_SECTION},
            {".section", Token::SECTION}};

        inline static std::unordered_map<std::string, Token> section_types_map = {
            {"%progbits", Token::SHT_PROGBITS},
            {"%nobits", Token::SHT_NOBITS},
            {"%note", Token::SHT_NOTE},
            {"%init_array", Token::SHT_INIT_ARRAY},
            {"%fini_array", Token::SHT_FINI_ARRAY},
            {"%preinit_array", Token::SHT_PREINIT_ARRAY}};

        inline static std::unordered_map<std::string, Token> type_map = {
            {"%function", Token::FUNCTION},
            {"%object", Token::OBJECT},
            {"%tls_object", Token::TLS_OBJECT}};

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
        
        // Ror har extr som et alias
        inline static std::unordered_map<std::string, Token> arithmetic_map = {
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
        inline static std::unordered_map<std::string, Token> logical_map = {
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
            {"cmp", Token::CMP}};
        inline static std::unordered_map<std::string, Token> conditional_map = {
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

        inline static std::unordered_map<std::string, Token> load_map = {
            {"ldr", Token::LDR},
            {"ldbr", Token::LDRB},
            {"ldrh", Token::LDRH},
            {"ldrw", Token::LDRW},
            {"ldmia", Token::LDMIA},
            {"ldp", Token::LDP},
        };
        inline static std::unordered_map<std::string, Token> store_map = {
            {"str", Token::STR},
            {"strb", Token::STRB},
            {"strh", Token::STRH},
            {"strw", Token::STRW},
            {"stmia", Token::STMIA},
            {"stp", Token::STP},
        };

        inline static std::unordered_map<std::string, Token> cfi_map = {
            {".cfi_startproc", Token::CFI_STARTPROC},
            {".cfi_endproc", Token::CFI_ENDPROC},
            {".cfi_sections", Token::CFI_SECTIONS},
            {".cfi_personality", Token::CFI_PERSONALITY},
            {".cfi_personality_id", Token::CFI_PERSONALITY_ID},
            {".cfi_fde_data", Token::CFI_FDE_DATA},
            {".cfi_lsda", Token::CFI_LSDA},
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
            {".cfi_debug_frame", Token::CFI_DEBUG_FRAME}};

        inline static std::unordered_map<std::string, Token> registers_map = {
            {"w0", Token::W0},
            {"w1", Token::W1},
            {"w2", Token::W2},
            {"w3", Token::W3},
            {"w4", Token::W4},
            {"w5", Token::W5},
            {"w6", Token::W6},
            {"w7", Token::W7},
            {"w8", Token::W8},
            {"w9", Token::W9},
            {"w10", Token::W10},
            {"w11", Token::W11},
            {"w12", Token::W12},
            {"w13", Token::W13},
            {"w14", Token::W14},
            {"w15", Token::W15},
            {"w16", Token::W16},
            {"w17", Token::W17},
            {"w18", Token::W18},
            {"w19", Token::W19},
            {"w20", Token::W20},
            {"w21", Token::W21},
            {"w22", Token::W22},
            {"w23", Token::W23},
            {"w24", Token::W24},
            {"w25", Token::W25},
            {"w26", Token::W26},
            {"w27", Token::W27},
            {"w28", Token::W28},
            {"w29", Token::W29},
            {"w30", Token::W30},
            {"wsp", Token::WSP},
            {"wzr", Token::WZR},
            {"x0", Token::X0},
            {"x1", Token::X1},
            {"x2", Token::X2},
            {"x3", Token::X3},
            {"x4", Token::X4},
            {"x5", Token::X5},
            {"x6", Token::X6},
            {"x7", Token::X7},
            {"x8", Token::X8},
            {"x9", Token::X9},
            {"x10", Token::X10},
            {"x11", Token::X11},
            {"x12", Token::X12},
            {"x13", Token::X13},
            {"x14", Token::X14},
            {"x15", Token::X15},
            {"x16", Token::X16},
            {"x17", Token::X17},
            {"x18", Token::X18},
            {"x19", Token::X19},
            {"x20", Token::X20},
            {"x21", Token::X21},
            {"x22", Token::X22},
            {"x23", Token::X23},
            {"x24", Token::X24},
            {"x25", Token::X25},
            {"x26", Token::X26},
            {"x27", Token::X27},
            {"x28", Token::X28},
            {"x29", Token::X29},
            {"x30", Token::X30},
            {"sp", Token::SP},
            {"xzr", Token::XZR},
            {"v0", Token::V0},
            {"v1", Token::V1},
            {"v2", Token::V2},
            {"v3", Token::V3},
            {"v4", Token::V4},
            {"v5", Token::V5},
            {"v6", Token::V6},
            {"v7", Token::V7},
            {"v8", Token::V8},
            {"v9", Token::V9},
            {"v10", Token::V10},
            {"v11", Token::V11},
            {"v12", Token::V12},
            {"v13", Token::V13},
            {"v14", Token::V14},
            {"v15", Token::V15},
            {"v16", Token::V16},
            {"v17", Token::V17},
            {"v18", Token::V18},
            {"v19", Token::V19},
            {"v20", Token::V20},
            {"v21", Token::V21},
            {"v22", Token::V22},
            {"v23", Token::V23},
            {"v24", Token::V24},
            {"v25", Token::V25},
            {"v26", Token::V26},
            {"v27", Token::V27},
            {"v28", Token::V28},
            {"v29", Token::V29},
            {"v30", Token::V30},
            {"v31", Token::V31},
            {"d0", Token::D0},
            {"d1", Token::D1},
            {"d2", Token::D2},
            {"d3", Token::D3},
            {"d4", Token::D4},
            {"d5", Token::D5},
            {"d6", Token::D6},
            {"d7", Token::D7},
            {"d8", Token::D8},
            {"d9", Token::D9},
            {"d10", Token::D10},
            {"d11", Token::D11},
            {"d12", Token::D12},
            {"d13", Token::D13},
            {"d14", Token::D14},
            {"d15", Token::D15},
            {"d16", Token::D16},
            {"d17", Token::D17},
            {"d18", Token::D18},
            {"d19", Token::D19},
            {"d20", Token::D20},
            {"d21", Token::D21},
            {"d22", Token::D22},
            {"d23", Token::D23},
            {"d24", Token::D24},
            {"d25", Token::D25},
            {"d26", Token::D26},
            {"d27", Token::D27},
            {"d28", Token::D28},
            {"d29", Token::D29},
            {"d30", Token::D30},
            {"d31", Token::D31},
            {"s0", Token::S0},
            {"s1", Token::S1},
            {"s2", Token::S2},
            {"s3", Token::S3},
            {"s4", Token::S4},
            {"s5", Token::S5},
            {"s6", Token::S6},
            {"s7", Token::S7},
            {"s8", Token::S8},
            {"s9", Token::S9},
            {"s10", Token::S10},
            {"s11", Token::S11},
            {"s12", Token::S12},
            {"s13", Token::S13},
            {"s14", Token::S14},
            {"s15", Token::S15},
            {"s16", Token::S16},
            {"s17", Token::S17},
            {"s18", Token::S18},
            {"s19", Token::S19},
            {"s20", Token::S20},
            {"s21", Token::S21},
            {"s22", Token::S22},
            {"s23", Token::S23},
            {"s24", Token::S24},
            {"s25", Token::S25},
            {"s26", Token::S26},
            {"s27", Token::S27},
            {"s28", Token::S28},
            {"s29", Token::S29},
            {"s30", Token::S30},
            {"s31", Token::S31},
            {"h0", Token::H0},
            {"h1", Token::H1},
            {"h2", Token::H2},
            {"h3", Token::H3},
            {"h4", Token::H4},
            {"h5", Token::H5},
            {"h6", Token::H6},
            {"h7", Token::H7},
            {"h8", Token::H8},
            {"h9", Token::H9},
            {"h10", Token::H10},
            {"h11", Token::H11},
            {"h12", Token::H12},
            {"h13", Token::H13},
            {"h14", Token::H14},
            {"h15", Token::H15},
            {"h16", Token::H16},
            {"h17", Token::H17},
            {"h18", Token::H18},
            {"h19", Token::H19},
            {"h20", Token::H20},
            {"h21", Token::H21},
            {"h22", Token::H22},
            {"h23", Token::H23},
            {"h24", Token::H24},
            {"h25", Token::H25},
            {"h26", Token::H26},
            {"h27", Token::H27},
            {"h28", Token::H28},
            {"h29", Token::H29},
            {"h30", Token::H30},
            {"h31", Token::H31},
            {"b0", Token::B0},
            {"b1", Token::B1},
            {"b2", Token::B2},
            {"b3", Token::B3},
            {"b4", Token::B4},
            {"b5", Token::B5},
            {"b6", Token::B6},
            {"b7", Token::B7},
            {"b8", Token::B8},
            {"b9", Token::B9},
            {"b10", Token::B10},
            {"b11", Token::B11},
            {"b12", Token::B12},
            {"b13", Token::B13},
            {"b14", Token::B14},
            {"b15", Token::B15},
            {"b16", Token::B16},
            {"b17", Token::B17},
            {"b18", Token::B18},
            {"b19", Token::B19},
            {"b20", Token::B20},
            {"b21", Token::B21},
            {"b22", Token::B22},
            {"b23", Token::B23},
            {"b24", Token::B24},
            {"b25", Token::B25},
            {"b26", Token::B26},
            {"b27", Token::B27},
            {"b28", Token::B28},
            {"b29", Token::B29},
            {"b30", Token::B30},
            {"b31", Token::B31},

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

    };
    // End of namespace Tokens
} // End of namespace ARM

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
//   .section	.note.GNU-stack,",@progbits