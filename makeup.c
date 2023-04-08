#include <stdio.h>

void swapper(int* val1, int* val2);
void readitall();
void isiteven(int value);
void twostr(char first[], char second[]);
void readfile(int n);
void theOwner();
void hideit();
void sorts();

int comp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    //variables to use with some of the functions
	int a = 5, b = 3, c = 9;
    char m[100] = "hello", z[100] = "Earth";
    char n[15] = "Cheese", y[] = "Pizza";

    //calling the functions
	swapper(&a, &b);
	swapper(&c,&a);

	readitall();
   
    twostr(m, z);
    twostr(n, y);

    theOwner();

    hideit();

    sorts();

	return 0;
}


//question 2.c value swap
void swapper(int* val1, int* val2) {

    printf("First Value: %d - Second Value: %d\n", *val1, *val2);
    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;
    printf("Swapped:: First Value: %d - Second Value: %d\n", *val1, *val2);
    printf("\n");
}

//question 2.a using getchar()
void readitall() {

    int ch;

    printf("Enter some Text and hit enter. use ctrl + d to exit input mode.\n");
    while ((ch = getchar()) != EOF) {
        putchar(ch);
    }
    printf("\n");
}
//question 2.b boolean
void isiteven(int value) {
    if ((value % 2) == 0) {
        printf("It is True the number is even");
    }
    if ((value % 2) > 0){
        printf("It is False the number is odd");
    }
}
//question 2.e two string cat without using strcat
void twostr(char first[], char second[]) {

    char output[100];
    int i = 0, n = 0;

    while (first[i] != '\0') {
        output[n] = first[i];
        i++;
        n++;
    }

    i = 0;
    while (second[i] != '\0') {
        output[n] = second[i];
        i++;
        n++;
    }
    output[n] = '\0';
    printf("%s\n", output);

}
//question 4.a
void readfile(int n) {
    FILE* fp;
    int c;
   
    fp = fopen("file.txt", "r");
    fseek(fp, (128*n), SEEK_SET);
    while (1) {
        c = fgetc(fp);
        if (feof(fp)) {
            break;
        }
        putchar(c);
    }
 }
//question 4.b finding the owner of a file
void theOwner() {
    struct stat st;
    struct passwd* pwd;

    stat("/home/justin.polchies/code/words", &st);
    if ((pwd = getpwuid(st.st_uid)) != NULL) {
        printf("%s\n", pwd->pw_name);
    }
}
//question 4.d disable and re able echo.
void hideit() {

    struct termios keys;
    int ch;

    tcgetattr(0, &keys);
    //turn echo off
    keys.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &keys);

    printf("password: ");

    while ((ch = getchar()) != EOF) {
        putchar(ch);
    }


    //turn echo on
    tcgetattr(0, &keys);
    keys.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &keys);
    printf("\n");
}
//question 5.e using qsort() on an array.
void sorts() {
    int val[] = { 88, 56, 100, 2, 25 };

    qsort(val, 5, sizeof(int), comp);

    for (int i = 0; i < 5; i++) {
        printf("%d\n", val[i]);
    }
}
