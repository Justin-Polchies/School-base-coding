#include <stdio.h>
#include <unistd.h> //usleep would not work unless this was included

int main() {

    //
    FILE *newFile;
    char ch[100] = "Another rides the Bus and another one goes and another ones goes. Another one Rides the Buss\n";

   
    newFile = fopen("file_1.txt", "w");

    if (newFile == NULL) {
        printf("File does not Exist\n");
    }
    else {
        while (1) {
            fputs(ch, newFile);
            usleep(50000);
        }
    }




    fclose(newFile);
    return 0;
}
