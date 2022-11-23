namespace LEG_TOKENS{
    //stp x29, x30, (sp, -48)!

#include <unordered_map>
#define INSTRUCTIONS \
  X(STP, "stp") \

#define REGISTERS \
  X(X29, "x29") \
  X(X30, "x30") \
  X(SP, "sp") \

#define MODIFIERS \
  X(EXCLAMATION, "!") \

#define SYMBOLS    \
  X(EOF_TOKEN)     \
  X(COLON)         \
  X(EQUAL_SIGN)    \
  X(L_BRACKET)     \
  X(R_BRACKET)     \
  X(L_PARA)        \
  X(R_PARA)        \
  X(R_ARROW)       \
  X(GREATER_THAN)  \
  X(LESS_THAN)     \
  X(HASH_SIGN)     \
  X(HASHHASH_SIGN) \
  X(DOLLAR_SIGN)   \
  X(PLUS_SIGN)     \
  X(LINE_COMMENT)  \
  X(COMMENT_START) \
  X(COMMENT_END)   \
  X(AT_SIGN)       \
  X(EOL_TOKEN)
}
