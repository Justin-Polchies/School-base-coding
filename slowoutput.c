#include <stdio.h>
#include <unistd.h> //usleep would not work unless this was included

int main() {

    //create a pointer for a file and the string to add to a file.
    FILE *newFile;
    char ch[100] = "Another rides the Bus and another one goes and another ones goes. Another one Rides the Buss\n";

   //opening the file if it exist. Should create the text file if its not there.
    newFile = fopen("file_1.txt", "w");

    //Makes sure that the file is there or was created. Throw error message if it can't find it
    if (newFile == NULL) {
        printf("File does not Exist\n");
    }
    else {
        //
        while (1) {
            fputs(ch, newFile);
            usleep(50000);
        }
    }




    fclose(newFile);
    return 0;
}
