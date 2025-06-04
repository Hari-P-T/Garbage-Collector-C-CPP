#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Collector.h"

Trash_Stack Collector = {NULL, 0};
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void push(void* ptr) {
    pthread_mutex_lock(&lock);
    Trash* temp = (Trash*)malloc(sizeof(Trash));
    if (!temp) {
        fprintf(stderr, "Failed to allocate memory for Trash node\n");
        pthread_mutex_unlock(&lock);
        exit(EXIT_FAILURE);
    }
    temp->pointer = ptr;
    temp->next = Collector.head;
    Collector.head = temp;
    Collector.size++;
    pthread_mutex_unlock(&lock);
}

void pop() {
    pthread_mutex_lock(&lock);
    if (Collector.size == 0) {
        fprintf(stderr, "Stack underflow\n");
        pthread_mutex_unlock(&lock);
        return;
    }

    Trash* temp = Collector.head;
    Collector.head = Collector.head->next;
    free(temp->pointer);
    free(temp);
    Collector.size--;
    pthread_mutex_unlock(&lock);
}

int is_empty() {
    pthread_mutex_lock(&lock);
    int empty = (Collector.size == 0);
    pthread_mutex_unlock(&lock);
    return empty;
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
    if (!ptr) return custom_malloc(size);

    void* new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&lock);
    Trash** current = &Collector.head;
    while (*current) {
        if ((*current)->pointer == ptr) {
            Trash* to_delete = *current;
            *current = (*current)->next;
            free(to_delete);
            Collector.size--;
            break;
        }
        current = &((*current)->next);
    }
    pthread_mutex_unlock(&lock);

    push(new_ptr);
    return new_ptr;
}

void custom_free(void* ptr) {
    if (!ptr) return;

    pthread_mutex_lock(&lock);
    Trash** current = &Collector.head;
    while (*current) {
        if ((*current)->pointer == ptr) {
            Trash* to_delete = *current;
            *current = (*current)->next;
            free(to_delete);
            Collector.size--;
            break;
        }
        current = &((*current)->next);
    }
    pthread_mutex_unlock(&lock);

    free(ptr);
}
