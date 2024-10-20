#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Collector.h"

Trash_Stack Collector = {NULL, 0};

void push(void* ptr) {
    Trash* temp = (Trash*)malloc(sizeof(Trash));
    if (!temp) {
        fprintf(stderr, "Failed to allocate memory for Trash node\n");
        exit(EXIT_FAILURE);
    }
    temp->pointer = ptr;
    temp->next = Collector.head;
    Collector.head = temp;
    Collector.size++;
}

void pop() {
    if (Collector.size == 0) {
        fprintf(stderr, "Stack underflow\n");
        return;
    }

    Trash* temp = Collector.head;
    Collector.head = Collector.head->next;
    free(temp->pointer);
    free(temp);
    Collector.size--;
}

int is_empty() {
    return Collector.size == 0;
}

void clean() {
    printf("Starting cleanup...\n");
    while (!is_empty()) {
        pop();
    }
    printf("Collector emptied: %d\n", is_empty());
}

void* custom_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    push(ptr);
    return ptr;
}

void* custom_calloc(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    push(ptr);
    return ptr;
}

void* custom_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    push(new_ptr);
    return new_ptr;
}

void custom_free(void* ptr) {
    free(ptr);
}
