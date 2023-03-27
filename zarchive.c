#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


int checkForFile(char* argv[]);
void checkForDir();


struct header {

    unsigned int uid;
    char owner[64];
    unsigned int files_tot;
    unsigned int options;
};

struct file {
    size_t size;
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
            archive();
        }

        if (!strcmp(argv[1], "x")) {
            printf("finding file now.\n");
        }
    }


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

void archive() {

    int n;
    struct dirent** files;

    printf("The Following is a list of files found in the Current Directory.\n");
    printf("\n");

    n = scandir(getcwd(NULL, 0), &files, NULL, alphasort);

    while (n--) {

        printf("%s\n", files[n]->d_name);
        free(files[n]);
    }


}

void unarhive() {

}

void getuserinfo() {
    getuid();
    getpwuid();
}