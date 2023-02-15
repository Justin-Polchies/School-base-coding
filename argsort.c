#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareStrings(const void* firstStr, const void* secondStr);

int main(int argc, char* argv[])
{   
    //pre initialized counters.
    int a = 0, i = 1;
    //get the size needed to make an char array big enough.
    char* charString[argc - 1];
    
    //check to make sure that user added strings to the command line.
    if (argc < 2) {
        printf("%s", "No string entered on the Command line.\n");
        return 0;
    }

    //fill a Char array with the argv values from the command line.
    for (; i < argc; i++) {
        charString[i - 1] = argv[i];
    }


    int charSize = argc - 1;
    //sort the strings by length
    qsort(charString, charSize, sizeof(char*), compareStrings);

    //Print out the results from qsort
    for (; a < charSize; a++) {
        printf("%s \n", charString[a]);
    }
    return 0;
}

//to compare the strings and their lengths putting them in order by smaller to larger (length)
int compareStrings(const void* firstStr, const void* secondStr) {

    char* first_str = *(char**)firstStr;
    char* second_str = *(char**)secondStr;

    if (strlen(first_str) < strlen(second_str)) {
        return 0;
    }
    if (strlen(first_str) > strlen(second_str)) {
        return 1;
    }

    return strcmp(first_str, second_str);
}