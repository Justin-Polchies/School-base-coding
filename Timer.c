#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void TM() {
    struct timeval current;
    struct tm* local;

    gettimeofday(&current, NULL);

    local = localtime(&current.tv_sec);

    printf("Current Time : %d:%d:%d:%ld\n", local->tm_hour, local->tm_min, local->tm_sec, current.tv_usec);

}


int main() {

    struct itimerval time;
    struct sigaction sig;

    
    sig.sa_handler = TM;
    sigaction(SIGVTALRM, &sig, NULL);

    time.it_value.tv_sec = 0;
    time.it_value.tv_usec = 1000;

    time.it_interval.tv_sec = 0;
    time.it_interval.tv_usec = 1000;

    setitimer(ITIMER_VIRTUAL, &time, NULL);

    int n = 1, i = 0;
    while (n) {

        i += 1;
        n++;


        if (n > 500000) {
            n = 1;
        }
    }
    return 0;
}

