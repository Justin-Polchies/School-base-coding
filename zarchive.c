
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>



struct header {

    unsigned int uid;
    char owner[64];
    unsigned int files_tot;
    unsigned int options;
};

struct FileHeader {
    size_t size;
    time_t timestamp;
    char filename[256];
};



int checkForFile(int argc, char* argv[]);
void checkForDir();
void archive(int argc, char* argv[]);
void unarchive(int argc, char* argv[]);

int main(int argc, char* argv[]) {



    if (!(strcmp(argv[1], "c"))) {

        archive();
    }

    if (!strcmp(argv[1], "x")) {
        unarchive();
    }




    return 0;
}

int checkForFile(int argc, char* argv[]) {

    printf("%s\n", argv[3]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[0]);

    printf("%d\n", argc);
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

void archive(int argc, char* argv[]) {


    uid_t idn;
    struct header h;
    idn = geteuid();
    struct passwd* pw = getpwuid(idn);
    strcpy(h.owner, pw->pw_name);

    int n, totalfiles;
    char line[128], temp[3], arcname[25];
    struct dirent** files;
    FILE* fp;


    printf("The Following is a list of files found in the Current Directory.\n");
    printf("\n");

    n = scandir(getcwd(NULL, 0), &files, NULL, alphasort);

    while (n--) {

        printf("%s\n", files[n]->d_name);
        free(files[n]);
    }
    printf("How many files are you archiving today?\n");
    fgets(temp, sizeof(temp), stdin);
    totalfiles = atoi(temp);
    h.files_tot = totalfiles;

    struct FileHeader fh[totalfiles];

    FILE* fwr;
    if (argc <= 2) {
        printf("No Archive file name was given. Please enter one now\n");
        fgets(arcname, sizeof(arcname), stdin);
        strtok(arcname, "\n");
        strcat(arcname, ".txt");
    }

    if (arcname != NULL) {

        fwr = fopen(arcname, "w");
        fwrite(&h, sizeof(struct header), 1, fwr);
    }


    for (int i = 0; i < totalfiles; i++) {

        printf("What File you want to archive?\n");
        fgets(line, sizeof(line), stdin);
        strtok(line, "\n");

        fp = fopen(line, "r");
        if (fp == NULL) {

            printf("NO FILE FOUND!!!!!!\n");
        }

        fseek(fp, 0, SEEK_END);
        fh[i].size = ftell(fp);
        strcpy(fh[i].filename, line);
        fh[i].timestamp = time(0);
        fseek(fp, 0, SEEK_SET);
        fwrite(&fh, sizeof(struct FileHeader), 1, fwr);

        char ch;
        ch = fgetc(fp);

        while (ch != EOF) {
            fputc(ch, fwr);
            ch = fgetc(fp);
        }
        printf("\nCopied good.\n");
    }

    fclose(fp);
    fclose(fwr);
}

void unarchive() {


}
