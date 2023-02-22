#include <stdio.h>
#include <stdlib.h>


int main() {
    int i = 0, end = 1001;
    char* ptr[end];

    for (; i < end; i++) {
        ptr[i] = (char*)malloc(sizeof(char));

    }
    printf("First address: %p\n", (void*)ptr[0]);
    printf("Last address: %p\n", (void*)ptr[end - 1]);
    return 0;
}

