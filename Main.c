#include <stdio.h>
#include <string.h>
#include "Collector.h"

int main() {
    atexit(clean);

    int* p1 = (int*)custom_malloc(sizeof(int));
    *p1 = 10;

    float* p2 = (float*)custom_malloc(sizeof(float));
    *p2 = 20.2020;

    char* p3 = (char*)custom_malloc(20 * sizeof(char));
    strcpy(p3, "hola");

    return 0;
}
