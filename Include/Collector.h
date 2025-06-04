#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <stddef.h>

typedef struct Trash {
    void* pointer;
    struct Trash* next;
} Trash;

typedef struct {
    Trash* head;
    int size;
} Trash_Stack;

extern Trash_Stack Collector;

void push(void* ptr);
void pop();
int is_empty();
void clean();

void* custom_malloc(size_t size);
void* custom_calloc(size_t num, size_t size);
void* custom_realloc(void* ptr, size_t size);
void custom_free(void* ptr);

#endif
