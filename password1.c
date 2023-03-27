// ask user for password with no echoing typing
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>


#define BUFSIZE 100
char buf[BUFSIZE];
int main()
{
    struct termios info, newIn;

    tcgetattr(0, &info);         /* get attribs   */

    info.c_lflag &= ~ECHO;      /* turn off echo bit   */
    tcsetattr(0, TCSANOW, &info);   /* set attribs */

    printf("password: ");
    char* passwd = get_passwd();
    printf("you entered: %s\n", passwd);

    // turn the echo bit back on before exiting !!!
    tcgetattr(0, &info);         /* get attribs   */
    info.c_lflag |= ECHO;       /* turn on echo bit   */
    tcsetattr(0, TCSANOW, &info);   /* set attribs */
}





    int c, len = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        buf[len++] = c;
        putchar('*');
        if (len == BUFSIZE - 1)
            break;
    }
    buf[len] = 0;    // terminate string
    putchar('\n');   // output the newline
    return buf;

