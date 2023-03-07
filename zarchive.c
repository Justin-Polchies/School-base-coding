#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


int checkForFile(char* argv[]);
void checkForDir();


int main(int argc, char* argv[]) {

    if (checkForFile(argv) == 0) {

        printf("Error: No File Found\n");
    }
    else {
        if (!(strcmp(argv[1], "c"))) {
            printf("Archiving file.\n");
        }

        if (!strcmp(argv[1], "x")) {
            printf("finding file now.\n");
        }
    }

    checkForDir();
    return 0;
}

int checkForFile(char* argv[]) {

    struct stat buf;
    return (stat(argv[2], &buf) == 0);
}

void checkForDir() {
    struct stat dir = { 0 };


    char* cd;
    cd = getcwd(NULL, 0);

    strcat(cd, "/archive");
    printf("%s\n", cd);

    if (stat(cd, &dir) == -1) {
        mkdir(cd, 777);
    }
}

