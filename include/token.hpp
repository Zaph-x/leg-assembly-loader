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
#include "tokensets/move_tokens.hpp"

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
    MOVE_INSTRUCTIONS \
    X(RAW_STRING) \
    X(DEC_NUMBER)    \
    X(HEX_NUMBER)   \
    X(ARMV8_A) \
    X(LABEL)        \
    X(ERROR)

        enum class Token
        {
#define COND_INSTR(OP) OP, OP##EQ, OP##NE, OP##CS, OP##CC, OP##MI, OP##PL, OP##HS, OP##NV, OP##LO, OP##VS, OP##VC, OP##HI, OP##LS, OP##GE, OP##LT, OP##GT, OP##LE, OP##AL,  
#define COND_INSTR_(OP,LTR) OP##LTR, OP##EQ##LTR, OP##NE##LTR, OP##CS##LTR, OP##CC##LTR, OP##MI##LTR, OP##PL##LTR, OP##HS##LTR, OP##NV##LTR, OP##LO##LTR, OP##VS##LTR, OP##VC##LTR, OP##HI##LTR, OP##LS##LTR, OP##GE##LTR, OP##LT##LTR, OP##GT##LTR, OP##LE##LTR, OP##AL##LTR,  

#define COND_INSTR_S(OP) COND_INSTR(OP) OP##S, OP##EQS, OP##NES, OP##CSS, OP##CCS, OP##MIS, OP##PLS, OP##HSS, OP##NVS, OP##LOS, OP##VSS, OP##VCS, OP##HIS, OP##LSS, OP##GES, OP##LTS, OP##GTS, OP##LES, OP##ALS,
#define COND_INSTR_B(OP) OP##B, OP##EQB, OP##NEB, OP##CSB, OP##CCB, OP##MIB, OP##PLB, OP##HSB, OP##NVB, OP##LOB, OP##VSB, OP##VCB, OP##HIB, OP##LSB, OP##GEB, OP##LTB, OP##GTB, OP##LEB, OP##ALB,
#define COND_INSTR_T(OP) OP##T, OP##EQT, OP##NET, OP##CST, OP##CCT, OP##MIT, OP##PLT, OP##HST, OP##NVT, OP##LOT, OP##VST, OP##VCT, OP##HIT, OP##LST, OP##GET, OP##LTT, OP##GTT, OP##LET, OP##ALT,
#define COND_INSTR_BT(OP) COND_INSTR(OP) COND_INSTR_B(OP) COND_INSTR_T(OP) OP##BT, OP##EQBT, OP##NEBT, OP##CSBT, OP##CCBT, OP##MIBT, OP##PLBT, OP##HSBT, OP##NVBT, OP##LOBT, OP##VSBT, OP##VCBT, OP##HIBT, OP##LSBT, OP##GEBT, OP##LTBT, OP##GTBT, OP##LEBT, OP##ALBT,
#define X(OP) OP,
            TOKENS
#undef X
#undef COND_INSTR_S
#undef COND_INSTR_B
#undef COND_INSTR_T
#undef COND_INSTR_BT
#undef COND_INSTR
#undef COND_INSTR_
        };

        inline std::ostream &operator<<(std::ostream &os, const Token &c)
        {
            switch (c)
            {
#define COND_INSTR(OP) \
    case Token::OP: return os << #OP; \
    case Token::OP##EQ: return os << #OP "EQ"; \
    case Token::OP##NE: return os << #OP "NE"; \
    case Token::OP##CS: return os << #OP "CS"; \
    case Token::OP##CC: return os << #OP "CC"; \
    case Token::OP##MI: return os << #OP "MI"; \
    case Token::OP##PL: return os << #OP "PL"; \
    case Token::OP##HS: return os << #OP "HS"; \
    case Token::OP##NV: return os << #OP "NV"; \
    case Token::OP##LO: return os << #OP "LO"; \
    case Token::OP##VS: return os << #OP "VS"; \
    case Token::OP##VC: return os << #OP "VC"; \
    case Token::OP##HI: return os << #OP "HI"; \
    case Token::OP##LS: return os << #OP "LS"; \
    case Token::OP##GE: return os << #OP "GE"; \
    case Token::OP##LT: return os << #OP "LT"; \
    case Token::OP##GT: return os << #OP "GT"; \
    case Token::OP##LE: return os << #OP "LE"; \
    case Token::OP##AL: return os << #OP "AL"; 

#define COND_INSTR_S(OP) \
    COND_INSTR(OP) \
    case Token::OP##S: return os << #OP "S"; \
    case Token::OP##EQS: return os << #OP "EQS"; \
    case Token::OP##NES: return os << #OP "NES"; \
    case Token::OP##CSS: return os << #OP "CSS"; \
    case Token::OP##CCS: return os << #OP "CCS"; \
    case Token::OP##MIS: return os << #OP "MIS"; \
    case Token::OP##PLS: return os << #OP "PLS"; \
    case Token::OP##HSS: return os << #OP "HSS"; \
    case Token::OP##NVS: return os << #OP "NVS"; \
    case Token::OP##LOS: return os << #OP "LOS"; \
    case Token::OP##VSS: return os << #OP "VSS"; \
    case Token::OP##VCS: return os << #OP "VCS"; \
    case Token::OP##HIS: return os << #OP "HIS"; \
    case Token::OP##LSS: return os << #OP "LSS"; \
    case Token::OP##GES: return os << #OP "GES"; \
    case Token::OP##LTS: return os << #OP "LTS"; \
    case Token::OP##GTS: return os << #OP "GTS"; \
    case Token::OP##LES: return os << #OP "LES"; \
    case Token::OP##ALS: return os << #OP "ALS";

#define COND_INSTR_B(OP) \
    case Token::OP##B: return os << #OP "B"; \
    case Token::OP##EQB: return os << #OP "EQB"; \
    case Token::OP##NEB: return os << #OP "NEB"; \
    case Token::OP##CSB: return os << #OP "CSB"; \
    case Token::OP##CCB: return os << #OP "CCB"; \
    case Token::OP##MIB: return os << #OP "MIB"; \
    case Token::OP##PLB: return os << #OP "PLB"; \
    case Token::OP##HSB: return os << #OP "HSB"; \
    case Token::OP##NVB: return os << #OP "NVB"; \
    case Token::OP##LOB: return os << #OP "LOB"; \
    case Token::OP##VSB: return os << #OP "VSB"; \
    case Token::OP##VCB: return os << #OP "VCB"; \
    case Token::OP##HIB: return os << #OP "HIB"; \
    case Token::OP##LSB: return os << #OP "LSB"; \
    case Token::OP##GEB: return os << #OP "GEB"; \
    case Token::OP##LTB: return os << #OP "LTB"; \
    case Token::OP##GTB: return os << #OP "GTB"; \
    case Token::OP##LEB: return os << #OP "LEB"; \
    case Token::OP##ALB: return os << #OP "ALB";

#define COND_INSTR_T(OP) \
    case Token::OP##T: return os << #OP "T"; \
    case Token::OP##EQT: return os << #OP "EQT"; \
    case Token::OP##NET: return os << #OP "NET"; \
    case Token::OP##CST: return os << #OP "CST"; \
    case Token::OP##CCT: return os << #OP "CCT"; \
    case Token::OP##MIT: return os << #OP "MIT"; \
    case Token::OP##PLT: return os << #OP "PLT"; \
    case Token::OP##HST: return os << #OP "HST"; \
    case Token::OP##NVT: return os << #OP "NVT"; \
    case Token::OP##LOT: return os << #OP "LOT"; \
    case Token::OP##VST: return os << #OP "VST"; \
    case Token::OP##VCT: return os << #OP "VCT"; \
    case Token::OP##HIT: return os << #OP "HIT"; \
    case Token::OP##LST: return os << #OP "LST"; \
    case Token::OP##GET: return os << #OP "GET"; \
    case Token::OP##LTT: return os << #OP "LTT"; \
    case Token::OP##GTT: return os << #OP "GTT"; \
    case Token::OP##LET: return os << #OP "LET"; \
    case Token::OP##ALT: return os << #OP "ALT";

#define COND_INSTR_BT(OP) \
    case Token::OP##BT: return os << #OP "BT"; \
    case Token::OP##EQBT: return os << #OP "EQBT"; \
    case Token::OP##NEBT: return os << #OP "NEBT"; \
    case Token::OP##CSBT: return os << #OP "CSBT"; \
    case Token::OP##CCBT: return os << #OP "CCBT"; \
    case Token::OP##MIBT: return os << #OP "MIBT"; \
    case Token::OP##PLBT: return os << #OP "PLBT"; \
    case Token::OP##HSBT: return os << #OP "HSBT"; \
    case Token::OP##NVBT: return os << #OP "NVBT"; \
    case Token::OP##LOBT: return os << #OP "LOBT"; \
    case Token::OP##VSBT: return os << #OP "VSBT"; \
    case Token::OP##VCBT: return os << #OP "VCBT"; \
    case Token::OP##HIBT: return os << #OP "HIBT"; \
    case Token::OP##LSBT: return os << #OP "LSBT"; \
    case Token::OP##GEBT: return os << #OP "GEBT"; \
    case Token::OP##LTBT: return os << #OP "LTBT"; \
    case Token::OP##GTBT: return os << #OP "GTBT"; \
    case Token::OP##LEBT: return os << #OP "LEBT"; \
    case Token::OP##ALBT: return os << #OP "ALBT";

#define COND_INSTR_(OP, LTTR) \
    case Token::OP##LTTR: return os << #OP #LTTR; \
    case Token::OP##EQ##LTTR: return os << #OP "EQ" #LTTR; \
    case Token::OP##NE##LTTR: return os << #OP "NE" #LTTR; \
    case Token::OP##CS##LTTR: return os << #OP "CS" #LTTR; \
    case Token::OP##CC##LTTR: return os << #OP "CC" #LTTR; \
    case Token::OP##MI##LTTR: return os << #OP "MI" #LTTR; \
    case Token::OP##PL##LTTR: return os << #OP "PL" #LTTR; \
    case Token::OP##HS##LTTR: return os << #OP "HS" #LTTR; \
    case Token::OP##NV##LTTR: return os << #OP "NV" #LTTR; \
    case Token::OP##LO##LTTR: return os << #OP "LO" #LTTR; \
    case Token::OP##VS##LTTR: return os << #OP "VS" #LTTR; \
    case Token::OP##VC##LTTR: return os << #OP "VC" #LTTR; \
    case Token::OP##HI##LTTR: return os << #OP "HI" #LTTR; \
    case Token::OP##LS##LTTR: return os << #OP "LS" #LTTR; \
    case Token::OP##GE##LTTR: return os << #OP "GE" #LTTR; \
    case Token::OP##LT##LTTR: return os << #OP "LT" #LTTR; \
    case Token::OP##GT##LTTR: return os << #OP "GT" #LTTR; \
    case Token::OP##LE##LTTR: return os << #OP "LE" #LTTR; \
    case Token::OP##AL##LTTR: return os << #OP "AL" #LTTR;



#define X(OP)       \
    case Token::OP: \
        return os << #OP;
                TOKENS
#undef X
#undef COND_INSTR_B
#undef COND_INSTR_T
#undef COND_INSTR_BT
#undef COND_INSTR_S
#undef COND_INSTR
#undef COND_INSTR_

            default:
                return os << "Unknown";
            }
        };

        inline static std::unordered_map<std::string, Token> directives_map = {
            {".align", Token::ALIGN},
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

        // Define a map of all possible ARMV8 instructions
        inline static std::unordered_map<std::string, Token> arithmetic_instructions_map = {            
            {"add", Token::ADD},
            {"adds", Token::ADDS},
            {"addeq", Token::ADDEQ},
            {"addne", Token::ADDNE},
            {"addcs", Token::ADDCS},
            {"addhs", Token::ADDHS},
            {"addcc", Token::ADDCC},
            {"addlo", Token::ADDLO},
            {"addmi", Token::ADDMI},
            {"addpl", Token::ADDPL},
            {"addvs", Token::ADDVS},
            {"addvc", Token::ADDVC},
            {"addhi", Token::ADDHI},
            {"addls", Token::ADDLS},
            {"addge", Token::ADDGE},
            {"addlt", Token::ADDLT},
            {"addgt", Token::ADDGT},
            {"addle", Token::ADDLE},
            {"addal", Token::ADDAL},
            {"addnv", Token::ADDNV},
            {"addeqs", Token::ADDEQS},
            {"addnes", Token::ADDNES},
            {"addcss", Token::ADDCSS},
            {"addhss", Token::ADDHSS},
            {"addccs", Token::ADDCCS},
            {"addlos", Token::ADDLOS},
            {"addmis", Token::ADDMIS},
            {"addpls", Token::ADDPLS},
            {"addvss", Token::ADDVSS},
            {"addvcs", Token::ADDVCS},
            {"addhis", Token::ADDHIS},
            {"addlss", Token::ADDLSS},
            {"addges", Token::ADDGES},
            {"addlts", Token::ADDLTS},
            {"addgts", Token::ADDGTS},
            {"addles", Token::ADDLES},
            {"addals", Token::ADDALS},
            {"addnvs", Token::ADDNVS},
            {"adc", Token::ADC},
            {"adcs", Token::ADCS},
            {"adceq", Token::ADCEQ},
            {"adcne", Token::ADCNE},
            {"adccs", Token::ADCCS},
            {"adchs", Token::ADCHS},
            {"adccc", Token::ADCCC},
            {"adclo", Token::ADCLO},
            {"adcmi", Token::ADCMI},
            {"adcpl", Token::ADCPL},
            {"adcvs", Token::ADCVS},
            {"adcvc", Token::ADCVC},
            {"adchi", Token::ADCHI},
            {"adcls", Token::ADCLS},
            {"adcge", Token::ADCGE},
            {"adclt", Token::ADCLT},
            {"adcgt", Token::ADCGT},
            {"adcle", Token::ADCLE},
            {"adcal", Token::ADCAL},
            {"adcnv", Token::ADCNV},
            {"adceqs", Token::ADCEQS},
            {"adcnes", Token::ADCNES},
            {"adccss", Token::ADCCSS},
            {"adchss", Token::ADCHSS},
            {"adcccs", Token::ADCCCS},
            {"adclos", Token::ADCLOS},
            {"adcmis", Token::ADCMIS},
            {"adcpls", Token::ADCPLS},
            {"adcvss", Token::ADCVSS},
            {"adcvcs", Token::ADCVCS},
            {"adchis", Token::ADCHIS},
            {"adclss", Token::ADCLSS},
            {"adcges", Token::ADCGES},
            {"adclts", Token::ADCLTS},
            {"adcgts", Token::ADCGTS},
            {"adcles", Token::ADCLES},
            {"adcals", Token::ADCALS},
            {"adcnvs", Token::ADCNVS},
            {"sub", Token::SUB},
            {"subs", Token::SUBS},
            {"subeq", Token::SUBEQ},
            {"subne", Token::SUBNE},
            {"subcs", Token::SUBCS},
            {"subhs", Token::SUBHS},
            {"subcc", Token::SUBCC},
            {"sublo", Token::SUBLO},
            {"submi", Token::SUBMI},
            {"subpl", Token::SUBPL},
            {"subvs", Token::SUBVS},
            {"subvc", Token::SUBVC},
            {"subhi", Token::SUBHI},
            {"subls", Token::SUBLS},
            {"subge", Token::SUBGE},
            {"sublt", Token::SUBLT},
            {"subgt", Token::SUBGT},
            {"suble", Token::SUBLE},
            {"subal", Token::SUBAL},
            {"subnv", Token::SUBNV},
            {"subeqs", Token::SUBEQS},
            {"subnes", Token::SUBNES},
            {"subcss", Token::SUBCSS},
            {"subhss", Token::SUBHSS},
            {"subccs", Token::SUBCCS},
            {"sublos", Token::SUBLOS},
            {"submis", Token::SUBMIS},
            {"subpls", Token::SUBPLS},
            {"subvss", Token::SUBVSS},
            {"subvcs", Token::SUBVCS},
            {"subhis", Token::SUBHIS},
            {"sublss", Token::SUBLSS},
            {"subges", Token::SUBGES},
            {"sublts", Token::SUBLTS},
            {"subgts", Token::SUBGTS},
            {"subles", Token::SUBLES},
            {"subals", Token::SUBALS},
            {"subnvs", Token::SUBNVS},
            {"sbc", Token::SBC},
            {"sbcs", Token::SBCS},
            {"sbceq", Token::SBCEQ},
            {"sbcne", Token::SBCNE},
            {"sbccs", Token::SBCCS},
            {"sbchs", Token::SBCHS},
            {"sbccc", Token::SBCCC},
            {"sbclo", Token::SBCLO},
            {"sbcmi", Token::SBCMI},
            {"sbcpl", Token::SBCPL},
            {"sbcvs", Token::SBCVS},
            {"sbcvc", Token::SBCVC},
            {"sbchi", Token::SBCHI},
            {"sbcls", Token::SBCLS},
            {"sbcge", Token::SBCGE},
            {"sbclt", Token::SBCLT},
            {"sbcgt", Token::SBCGT},
            {"sbcle", Token::SBCLE},
            {"sbcal", Token::SBCAL},
            {"sbcnv", Token::SBCNV},
            {"sbceqs", Token::SBCEQS},
            {"sbcnes", Token::SBCNES},
            {"sbccss", Token::SBCCSS},
            {"sbchss", Token::SBCHSS},
            {"sbcccs", Token::SBCCCS},
            {"sbclos", Token::SBCLOS},
            {"sbcmis", Token::SBCMIS},
            {"sbcpls", Token::SBCPLS},
            {"sbcvss", Token::SBCVSS},
            {"sbcvcs", Token::SBCVCS},
            {"sbchis", Token::SBCHIS},
            {"sbclss", Token::SBCLSS},
            {"sbcges", Token::SBCGES},
            {"sbclts", Token::SBCLTS},
            {"sbcgts", Token::SBCGTS},
            {"sbcles", Token::SBCLES},
            {"sbcals", Token::SBCALS},
            {"sbcnvs", Token::SBCNVS},
            {"rsb", Token::RSB},
            {"rsbs", Token::RSBS},
            {"rsbeq", Token::RSBEQ},
            {"rsbne", Token::RSBNE},
            {"rsbcs", Token::RSBCS},
            {"rsbhs", Token::RSBHS},
            {"rsbcc", Token::RSBCC},
            {"rsblo", Token::RSBLO},
            {"rsbmi", Token::RSBMI},
            {"rsbpl", Token::RSBPL},
            {"rsbvs", Token::RSBVS},
            {"rsbvc", Token::RSBVC},
            {"rsbhi", Token::RSBHI},
            {"rsbls", Token::RSBLS},
            {"rsbge", Token::RSBGE},
            {"rsblt", Token::RSBLT},
            {"rsbgt", Token::RSBGT},
            {"rsble", Token::RSBLE},
            {"rsbal", Token::RSBAL},
            {"rsbnv", Token::RSBNV},
            {"rsbeqs", Token::RSBEQS},
            {"rsbnes", Token::RSBNES},
            {"rsbcss", Token::RSBCSS},
            {"rsbhss", Token::RSBHSS},
            {"rsbccs", Token::RSBCCS},
            {"rsblos", Token::RSBLOS},
            {"rsbmis", Token::RSBMIS},
            {"rsbpls", Token::RSBPLS},
            {"rsbvss", Token::RSBVSS},
            {"rsbvcs", Token::RSBVCS},
            {"rsbhis", Token::RSBHIS},
            {"rsblss", Token::RSBLSS},
            {"rsbges", Token::RSBGES},
            {"rsblts", Token::RSBLTS},
            {"rsbgts", Token::RSBGTS},
            {"rsbles", Token::RSBLES},
            {"rsbals", Token::RSBALS},
            {"rsbnvs", Token::RSBNVS},
            {"rsc", Token::RSC},
            {"rscs", Token::RSCS},
            {"rsceq", Token::RSCEQ},
            {"rscne", Token::RSCNE},
            {"rsccs", Token::RSCCS},
            {"rschs", Token::RSCHS},
            {"rsccc", Token::RSCCC},
            {"rsclo", Token::RSCLO},
            {"rscmi", Token::RSCMI},
            {"rscpl", Token::RSCPL},
            {"rscvs", Token::RSCVS},
            {"rscvc", Token::RSCVC},
            {"rschi", Token::RSCHI},
            {"rscls", Token::RSCLS},
            {"rscge", Token::RSCGE},
            {"rsclt", Token::RSCLT},
            {"rscgt", Token::RSCGT},
            {"rscle", Token::RSCLE},
            {"rscal", Token::RSCAL},
            {"rscnv", Token::RSCNV},
            {"rsceqs", Token::RSCEQS},
            {"rscnes", Token::RSCNES},
            {"rsccss", Token::RSCCSS},
            {"rschss", Token::RSCHSS},
            {"rscccs", Token::RSCCCS},
            {"rsclos", Token::RSCLOS},
            {"rscmis", Token::RSCMIS},
            {"rscpls", Token::RSCPLS},
            {"rscvss", Token::RSCVSS},
            {"rscvcs", Token::RSCVCS},
            {"rschis", Token::RSCHIS},
            {"rsclss", Token::RSCLSS},
            {"rscges", Token::RSCGES},
            {"rsclts", Token::RSCLTS},
            {"rscgts", Token::RSCGTS},
            {"rscles", Token::RSCLES},
            {"rscals", Token::RSCALS},
            {"rscnvs", Token::RSCNVS},
        };


        inline static std::unordered_map<std::string, Token> logical_instructions_map = {
            {"and", Token::AND},
            {"ands", Token::ANDS},
            {"andeq", Token::ANDEQ},
            {"andne", Token::ANDNE},
            {"andcs", Token::ANDCS},
            {"andhs", Token::ANDHS},
            {"andcc", Token::ANDCC},
            {"andlo", Token::ANDLO},
            {"andmi", Token::ANDMI},
            {"andpl", Token::ANDPL},
            {"andvs", Token::ANDVS},
            {"andvc", Token::ANDVC},
            {"andhi", Token::ANDHI},
            {"andls", Token::ANDLS},
            {"andge", Token::ANDGE},
            {"andlt", Token::ANDLT},
            {"andgt", Token::ANDGT},
            {"andle", Token::ANDLE},
            {"andal", Token::ANDAL},
            {"andnv", Token::ANDNV},
            {"andeqs", Token::ANDEQS},
            {"andnes", Token::ANDNES},
            {"andcss", Token::ANDCSS},
            {"andhss", Token::ANDHSS},
            {"andccs", Token::ANDCCS},
            {"andlos", Token::ANDLOS},
            {"andmis", Token::ANDMIS},
            {"andpls", Token::ANDPLS},
            {"andvss", Token::ANDVSS},
            {"andvcs", Token::ANDVCS},
            {"andhis", Token::ANDHIS},
            {"andlss", Token::ANDLSS},
            {"andges", Token::ANDGES},
            {"andlts", Token::ANDLTS},
            {"andgts", Token::ANDGTS},
            {"andles", Token::ANDLES},
            {"andals", Token::ANDALS},
            {"andnvs", Token::ANDNVS},
            {"eor", Token::EOR},
            {"eors", Token::EORS},
            {"eoreq", Token::EOREQ},
            {"eorne", Token::EORNE},
            {"eorcs", Token::EORCS},
            {"eorhs", Token::EORHS},
            {"eorcc", Token::EORCC},
            {"eorlo", Token::EORLO},
            {"eormi", Token::EORMI},
            {"eorpl", Token::EORPL},
            {"eorvs", Token::EORVS},
            {"eorvc", Token::EORVC},
            {"eorhi", Token::EORHI},
            {"eorls", Token::EORLS},
            {"eorge", Token::EORGE},
            {"eorlt", Token::EORLT},
            {"eorgt", Token::EORGT},
            {"eorle", Token::EORLE},
            {"eoral", Token::EORAL},
            {"eornv", Token::EORNV},
            {"eoreqs", Token::EOREQS},
            {"eornes", Token::EORNES},
            {"eorcss", Token::EORCSS},
            {"eorhss", Token::EORHSS},
            {"eorccs", Token::EORCCS},
            {"eorlos", Token::EORLOS},
            {"eormis", Token::EORMIS},
            {"eorpls", Token::EORPLS},
            {"eorvss", Token::EORVSS},
            {"eorvcs", Token::EORVCS},
            {"eorhis", Token::EORHIS},
            {"eorlss", Token::EORLSS},
            {"eorges", Token::EORGES},
            {"eorlts", Token::EORLTS},
            {"eorgts", Token::EORGTS},
            {"eorles", Token::EORLES},
            {"eorals", Token::EORALS},
            {"eornvs", Token::EORNVS},
            {"orr", Token::ORR},
            {"orrs", Token::ORRS},
            {"orreq", Token::ORREQ},
            {"orrne", Token::ORRNE},
            {"orrcs", Token::ORRCS},
            {"orrhs", Token::ORRHS},
            {"orrcc", Token::ORRCC},
            {"orrlo", Token::ORRLO},
            {"orrmi", Token::ORRMI},
            {"orrpl", Token::ORRPL},
            {"orrvs", Token::ORRVS},
            {"orrvc", Token::ORRVC},
            {"orrhi", Token::ORRHI},
            {"orrls", Token::ORRLS},
            {"orrge", Token::ORRGE},
            {"orrlt", Token::ORRLT},
            {"orrgt", Token::ORRGT},
            {"orrle", Token::ORRLE},
            {"orral", Token::ORRAL},
            {"orrnv", Token::ORRNV},
            {"orreqs", Token::ORREQS},
            {"orrnes", Token::ORRNES},
            {"orrcss", Token::ORRCSS},
            {"orrhss", Token::ORRHSS},
            {"orrccs", Token::ORRCCS},
            {"orrlos", Token::ORRLOS},
            {"orrmis", Token::ORRMIS},
            {"orrpls", Token::ORRPLS},
            {"orrvss", Token::ORRVSS},
            {"orrvcs", Token::ORRVCS},
            {"orrhis", Token::ORRHIS},
            {"orrlss", Token::ORRLSS},
            {"orrges", Token::ORRGES},
            {"orrlts", Token::ORRLTS},
            {"orrgts", Token::ORRGTS},
            {"orrles", Token::ORRLES},
            {"orrals", Token::ORRALS},
            {"orrnvs", Token::ORRNVS},
            {"bic", Token::BIC},
            {"bics", Token::BICS},
            {"biceq", Token::BICEQ},
            {"bicne", Token::BICNE},
            {"biccs", Token::BICCS},
            {"bichs", Token::BICHS},
            {"biccc", Token::BICCC},
            {"biclo", Token::BICLO},
            {"bicmi", Token::BICMI},
            {"bicpl", Token::BICPL},
            {"bicvs", Token::BICVS},
            {"bicvc", Token::BICVC},
            {"bichi", Token::BICHI},
            {"bicls", Token::BICLS},
            {"bicge", Token::BICGE},
            {"biclt", Token::BICLT},
            {"bicgt", Token::BICGT},
            {"bicle", Token::BICLE},
            {"bical", Token::BICAL},
            {"bicnv", Token::BICNV},
            {"biceqs", Token::BICEQS},
            {"bicnes", Token::BICNES},
            {"biccss", Token::BICCSS},
            {"bichss", Token::BICHSS},
            {"bicccs", Token::BICCCS},
            {"biclos", Token::BICLOS},
            {"bicmis", Token::BICMIS},
            {"bicpls", Token::BICPLS},
            {"bicvss", Token::BICVSS},
            {"bicvcs", Token::BICVCS},
            {"bichis", Token::BICHIS},
            {"biclss", Token::BICLSS},
            {"bicges", Token::BICGES},
            {"biclts", Token::BICLTS},
            {"bicgts", Token::BICGTS},
            {"bicles", Token::BICLES},
            {"bicals", Token::BICALS},
            {"bicnvs", Token::BICNVS}
        };

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

        inline static std::unordered_map<std::string, Token> mem_instruction_map = {
            {"adrp", Token::ADRP},
            {"adr", Token::ADR},
            {"adrl", Token::ADRL},
            {"ldr", Token::LDR},
            {"ldrb", Token::LDRB},
            {"ldrh", Token::LDRH},
            {"ldrt", Token::LDRT},
            {"ldrbt", Token::LDRBT},
            {"ldreq", Token::LDREQ},
            {"ldrne", Token::LDRNE},
            {"ldrcs", Token::LDRCS},
            {"ldrhs", Token::LDRHS},
            {"ldrcc", Token::LDRCC},
            {"ldrlo", Token::LDRLO},
            {"ldrmi", Token::LDRMI},
            {"ldrpl", Token::LDRPL},
            {"ldrvs", Token::LDRVS},
            {"ldrvc", Token::LDRVC},
            {"ldrhi", Token::LDRHI},
            {"ldrls", Token::LDRLS},
            {"ldrge", Token::LDRGE},
            {"ldrlt", Token::LDRLT},
            {"ldrgt", Token::LDRGT},
            {"ldrle", Token::LDRLE},
            {"ldral", Token::LDRAL},
            {"ldrnv", Token::LDRNV},
            {"ldreqb", Token::LDREQB},
            {"ldrneb", Token::LDRNEB},
            {"ldrcsb", Token::LDRCSB},
            {"ldrhsb", Token::LDRHSB},
            {"ldrccb", Token::LDRCCB},
            {"ldrlob", Token::LDRLOB},
            {"ldrhib", Token::LDRHIB},
            {"ldrlsb", Token::LDRLSB},
            {"ldrgeb", Token::LDRGEB},
            {"ldrltb", Token::LDRLTB},
            {"ldrgtb", Token::LDRGTB},
            {"ldrleb", Token::LDRLEB},
            {"ldralb", Token::LDRALB},
            {"ldrnvb", Token::LDRNVB},
            {"ldreqh", Token::LDREQH},
            {"ldrneh", Token::LDRNEH},
            {"ldrcsh", Token::LDRCSH},
            {"ldrhsh", Token::LDRHSH},
            {"ldrcch", Token::LDRCCH},
            {"ldrloh", Token::LDRLOH},
            {"ldrmih", Token::LDRMIH},
            {"ldrplh", Token::LDRPLH},
            {"ldrvsh", Token::LDRVSH},
            {"ldrvch", Token::LDRVCH},
            {"ldrhih", Token::LDRHIH},
            {"ldrlsh", Token::LDRLSH},
            {"ldrgeh", Token::LDRGEH},
            {"ldrlth", Token::LDRLTH},
            {"ldrgth", Token::LDRGTH},
            {"ldrleh", Token::LDRLEH},
            {"ldralh", Token::LDRALH},
            {"ldrnvh", Token::LDRNVH},
            {"ldreqt", Token::LDREQT},
            {"ldrnet", Token::LDRNET},
            {"ldrcst", Token::LDRCST},
            {"ldrhst", Token::LDRHST},
            {"ldrcct", Token::LDRCCT},
            {"ldrlot", Token::LDRLOT},
            {"ldrmit", Token::LDRMIT},
            {"ldrplt", Token::LDRPLT},
            {"ldrvst", Token::LDRVST},
            {"ldrvct", Token::LDRVCT},
            {"ldrhit", Token::LDRHIT},
            {"ldrlst", Token::LDRLST},
            {"ldrget", Token::LDRGET},
            {"ldrltt", Token::LDRLTT},
            {"ldrgtt", Token::LDRGTT},
            {"ldrlet", Token::LDRLET},
            {"ldralt", Token::LDRALT},
            {"ldrnvt", Token::LDRNVT},
            {"ldreqbt", Token::LDREQBT},
            {"ldrnebt", Token::LDRNEBT},
            {"ldrcsbt", Token::LDRCSBT},
            {"ldrhsbt", Token::LDRHSBT},
            {"ldrccbt", Token::LDRCCBT},
            {"ldrlobt", Token::LDRLOBT},
            {"ldrhibt", Token::LDRHIBT},
            {"ldrlsbt", Token::LDRLSBT},
            {"ldrgebt", Token::LDRGEBT},
            {"ldrltbt", Token::LDRLTBT},
            {"ldrgtbt", Token::LDRGTBT},
            {"ldrlebt", Token::LDRLEBT},
            {"ldralbt", Token::LDRALBT},
            {"ldrnvbt", Token::LDRNVBT},
            {"str", Token::STR},
            {"strb", Token::STRB},
            {"strh", Token::STRH},
            {"strt", Token::STRT},
            {"strbt", Token::STRBT},
            {"streq", Token::STREQ},
            {"strne", Token::STRNE},
            {"strcs", Token::STRCS},
            {"strhs", Token::STRHS},
            {"strcc", Token::STRCC},
            {"strlo", Token::STRLO},
            {"strmi", Token::STRMI},
            {"strpl", Token::STRPL},
            {"strvs", Token::STRVS},
            {"strvc", Token::STRVC},
            {"strhi", Token::STRHI},
            {"strls", Token::STRLS},
            {"strge", Token::STRGE},
            {"strlt", Token::STRLT},
            {"strgt", Token::STRGT},
            {"strle", Token::STRLE},
            {"stral", Token::STRAL},
            {"strnv", Token::STRNV},
            {"streqb", Token::STREQB},
            {"strneb", Token::STRNEB},
            {"strcsb", Token::STRCSB},
            {"strhsb", Token::STRHSB},
            {"strccb", Token::STRCCB},
            {"strlob", Token::STRLOB},
            {"strhib", Token::STRHIB},
            {"strlsb", Token::STRLSB},
            {"strgeb", Token::STRGEB},
            {"strltb", Token::STRLTB},
            {"strgtb", Token::STRGTB},
            {"strleb", Token::STRLEB},
            {"stralb", Token::STRALB},
            {"strnvb", Token::STRNVB},
            {"streqh", Token::STREQH},
            {"strneh", Token::STRNEH},
            {"strcsh", Token::STRCSH},
            {"strhsh", Token::STRHSH},
            {"strcch", Token::STRCCH},
            {"strloh", Token::STRLOH},
            {"strmih", Token::STRMIH},
            {"strplh", Token::STRPLH},
            {"strvsh", Token::STRVSH},
            {"strvch", Token::STRVCH},
            {"strhih", Token::STRHIH},
            {"strlsh", Token::STRLSH},
            {"strgeh", Token::STRGEH},
            {"strlth", Token::STRLTH},
            {"strgth", Token::STRGTH},
            {"strleh", Token::STRLEH},
            {"stralh", Token::STRALH},
            {"strnvh", Token::STRNVH},
            {"streqt", Token::STREQT},
            {"strnet", Token::STRNET},
            {"strcst", Token::STRCST},
            {"strhst", Token::STRHST},
            {"strcct", Token::STRCCT},
            {"strlot", Token::STRLOT},
            {"strmit", Token::STRMIT},
            {"strplt", Token::STRPLT},
            {"strvst", Token::STRVST},
            {"strvct", Token::STRVCT},
            {"strhit", Token::STRHIT},
            {"strlst", Token::STRLST},
            {"strget", Token::STRGET},
            {"strltt", Token::STRLTT},
            {"strgtt", Token::STRGTT},
            {"strlet", Token::STRLET},
            {"stralt", Token::STRALT},
            {"strnvt", Token::STRNVT},
            {"streqbt", Token::STREQBT},
            {"strnebt", Token::STRNEBT},
            {"strcsbt", Token::STRCSBT},
            {"strhsbt", Token::STRHSBT},
            {"strccbt", Token::STRCCBT},
            {"strlobt", Token::STRLOBT},
            {"strhibt", Token::STRHIBT},
            {"strlsbt", Token::STRLSBT},
            {"strgebt", Token::STRGEBT},
            {"strltbt", Token::STRLTBT},
            {"strgtbt", Token::STRGTBT},
            {"strlebt", Token::STRLEBT},
            {"stralbt", Token::STRALBT},
            {"strnvbt", Token::STRNVBT},
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
    };
    // End of namespace Tokens
} // End of namespace ARM

#endif
