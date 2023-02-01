#include <stdio.h>
#include <unistd.h>

int main() {

    FILE *theFile, * newFile;
    char ch;

    theFile = fopen("File_2.txt", "r");
    newFile = fopen("file_1.txt", "w");

    if (theFile == NULL) {
        printf("File does not Exist\n");
    }
    else {
        do {

            ch = fgetc(theFile);
            fputc(ch, newFile);
            usleep(50000);

        } while (ch != EOF);

    }




    fclose(newFile);
    fclose(theFile);

    return 0;
}
