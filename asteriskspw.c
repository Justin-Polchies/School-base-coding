#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <conio.h>

char* get_pw();

#define BUFSIZE 100
char buf[BUFSIZE];

int main() {
	
	struct termios info;

	tcgetattr(0, &info);
    info.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &info);

	printf("password: ");
	char* passwd = get_pw();
    
    
    tcgetattr(0, &info);         
    info.c_lflag |= ECHO;       
    tcsetattr(0, TCSANOW, &info);
}

}

char* get_pw()
{
    int c, len = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        buf[len++] = c;
        if (len == BUFSIZE - 1)
            break;
    }
    buf[len] = 0;    // terminate string
    putchar('\n');   // output the newline
    return buf;
}