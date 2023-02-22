#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


void compressIt(char* argv[], int n);

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("%s\n", "No file was added.");
    }
    if (argc > 2) {
        printf("%s\n", "To many inputs add.");
    }

    compressIt(argv, 8);

    return 0;
}


void compressIt(char* argv[], int n) {
    unsigned char* c = (char*)malloc(n * sizeof(char));

    printf("%s\n", argv[1]);

    int fOpener = open(argv[1], O_RDONLY);
    int fReader = read(fOpener, c, 250);
    int counter = 0;

    for (int i = 0; i < 8; i++) {
        printf("%d\n", !!((c[0] << i) & 0x80));
        
    }

    close(fOpener);

}


