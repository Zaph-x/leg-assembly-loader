#ifndef STORE_LOAD_TOKENS_HPP
#define STORE_LOAD_TOKENS_HPP


#define LOAD_OPS \
    X(LDR)\
    X(LDRB)\
    X(LDRH)\
    X(LDRW)\
    X(LDMIA)\
    X(LDP)
    
#define STORE_OPS \
    X(STR)\
    X(STRB)\
    X(STRH)\
    X(STRW)\
    X(STMIA)\
    X(STP)

#define LOAD_STORE_OPS \
    LOAD_OPS \
    STORE_OPS

#endif