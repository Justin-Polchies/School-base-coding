#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

openNew(char* prog, char** arg) {

    pid_t newProcess;

    newProcess = fork();

    if (newProcess != 0) {
        return newProcess;
    }
    else {
        execvp(prog, arg);
        abort()
    }

}

int main(int argc, char* argv[]) {
    
    char* arg = { "a.out","5","/",NULL };

    openNew("a.out", arg)

    return 0;
}
