#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


int checkForFile(char* argv[]);

struct header {
    unsigned int uid;
    char owner[64];
    unsigned int n_files;
    unsigned int options;
};

struct file {
    size_t size:
    time_t timestamp;
    char filename[256];
};





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
    char cc = argv[1][0];

    printf("%c\n", cc);
}

int checkForFile(char* argv[]) {

    struct stat buf;
    return (stat(argv[2], &buf) == 0);
}



