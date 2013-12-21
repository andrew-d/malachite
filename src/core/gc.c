#include <stddef.h>
#include <stdlib.h>

#include "gc.h"


void gc_init(gc_context_t* ctx) {
    ctx->list = NULL;
    ctx->bytes = 0;
}

void gc_run(gc_context_t* ctx) {
    /* TODO: do something here */
    ((void)ctx);

}

void* gc_alloc(gc_context_t* ctx, size_t size) {
    void* mem;
    gc_header_t* header;

    /* Get the memory */
    /* TODO: use custom allocator here */
    mem = malloc(size);

    /* Initialize header */
    header = (gc_header_t*)mem;
    header->next = ctx->list;
    ctx->list = header;

    /* Update context */
    ctx->bytes += size;

    /* Return actual object */
    return (void*)(((uintptr_t)mem) + sizeof(gc_header_t));
}
