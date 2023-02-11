#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
//void main() {

    int  oneChar, oldChar;

    do
    {
        oneChar = getc(stdin);
        
        if (oneChar == '\t') 
        {
            if (oldChar != '\t') 
            {
                printf("There was a tab");
                putchar(' ', stdout);;
            }
            else 
            {
                printf("Oldchar had no tab");
                oldChar = oneChar;
                oneChar = getc(stdin);
            }
        }
        else 
        {
            printf("no tab found");
            oldChar = oneChar;
            putchar(oneChar, stdout);
        }
    }while (oneChar != EOF);

   
}
