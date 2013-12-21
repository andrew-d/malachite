#pragma once
#ifndef _MALACHITE_GC_H
#define _MALACHITE_GC_H


/* GC header object */
typedef struct _gc_header_s {
    struct _gc_header_s* next;
} gc_header_t;

/* Context for a garbage collector */
typedef struct _gc_context_s {
    gc_header_t* list;
    size_t       bytes;
} gc_context_t;


/* Initialize the garbage collector */
void gc_init(gc_context_t* ctx);

/* Run the GC algorithm */
void gc_run(gc_context_t* ctx);

/* Allocate some memory from the GC */
void* gc_alloc(gc_context_t* ctx, size_t size);

/* TODO: use these */
void gc_read_barrier(gc_context_t* ctx, void* object);
void gc_write_barrier(gc_context_t* ctx, void* object);

#endif /* _MALACHITE_GC_H */
