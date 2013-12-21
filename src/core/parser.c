#include <stdio.h>
#include <stdlib.h>

#define YY_MALLOC(YY, SIZE)         malloc(SIZE)
#define YY_REALLOC(YY, PTR, SIZE)   realloc(PTR, SIZE)
#define YY_FREE(YY, PTR)            free(PTR)

#include "parser.leg.c"


void parse(char* code)
{
    yycontext ctx;
    memset(&ctx, 0, sizeof(yycontext));

    ctx.input = code;
    ctx.input_end = code + strlen(code);

    while( yyparse(&ctx) )
        ;

    printf("Found %d lines\n", ctx.lineno);
    yyrelease(&ctx);
}
