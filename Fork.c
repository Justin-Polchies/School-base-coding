#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    printf("Parent process: %d - Count: %d\n", getpid(), 5);

    for (int count = 1; count < 5; count++) {
        if (fork() == 0) {
            printf("Child process: %d - Count: %d\n", getpid(), count);
            //found out I need this call.
            //With out it the program would run twice
            exit(0);
        }
    }
    return 0;
}