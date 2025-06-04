#include <stdio.h>
#include <string.h>
#include "../include/Collector.h"

int main() {
    atexit(clean);

    int* nums = (int*)custom_calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++) nums[i] = i;

    nums = (int*)custom_realloc(nums, 10 * sizeof(int));
    for (int i = 5; i < 10; i++) nums[i] = i;

    char* str = (char*)custom_malloc(50);
    strcpy(str, "Reusable Thread-Safe Collector!");

    printf("Data: %s\n", str);

    return 0;
}
