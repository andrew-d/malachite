#pragma once
#ifndef _MALACHITE_PARSER_H
#define _MALACHITE_PARSER_H

typedef enum {
    NUMBER,
    FLOAT
} mch_token_type_t;

typedef struct _mch_token_s {
    int lineno;
} mch_token_t;

#endif /* _MALACHITE_PARSER_H */
