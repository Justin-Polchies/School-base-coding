#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ioctl.h>
//Not used.
#define MAXBUF 250000

//Struct to hold window information
struct winsizes{
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;

};

//Struct to hold file information and two other var for scroll control.
typedef struct {
	FILE *fp;
	size_t lineSpot;
	char *name;
	char *buf;
	long fileSize;
	int repeatLine;
	int speed;
} fileInfo;

//Global var to make it easier to deal with file read.
fileInfo file;

//functions and signal handler.
void singleLine();
void screenFull();
void fileToBuffer(char *filename);
void sigHandler(int signum){
	if(file.repeatLine){
		singleLine();	
	}
};

int main(int argc, char* argv[]) {

	struct itimerval time;
	struct winsize size;
	struct termios info, newIn;
	int LINELEN = 256;
	char  line[LINELEN];
	int i;


	if(argc < 1){
		printf("Please Indicate file to display.\n");
		return 0;
	}else{

		fileToBuffer(argv[1]);
		
	}
	//Setting Timer's settings
	time.it_value.tv_sec = file.speed;
	time.it_value.tv_usec = 0;	
	time.it_interval.tv_sec = file.speed;
	time.it_interval.tv_usec = 0;

	//Windows information. to get rows and cols
	ioctl(1, TIOCGWINSZ, &size);

	// shutting off echo and ICANON
	tcgetattr(0, &info);   
	newIn = info;
	info.c_lflag &= ~ECHO & ~ICANON;      
	tcsetattr(0, TCSANOW, &info);  

	//Displaying one page worth of information using the row information from the window.
	i = size.ws_row;
	screenFull(i);
	
	//starting the timer call for scrolling. 
	signal(SIGALRM, sigHandler);
	setitimer(ITIMER_REAL, &time, NULL);

	//using a while loop to capture the key press and handling which action to used using a switch statement **Could have been it's own function**.
	while(1){
		
		char keyPressed = getchar();

		switch(keyPressed){
			case 'q':
				printf("\033[7mExiting!\n\033[0m");
				// turn the echo bit back on before exiting !!!
				tcgetattr(0, &info);         /* get attribs   */
				info.c_lflag |= ECHO;       /* turn on echo bit   */
				tcsetattr(0, TCSANOW, &info);   /* set attribs */
			
				exit(0);
			
				break;
			case ' ':
				i = size.ws_row;
				file.repeatLine = 0;
				screenFull(i);
				break;
			case '\n':
			case '\r':
				file.repeatLine  = !file.repeatLine;
				break;
				//Next two cases control the timer speed, which controls the scroll speed.
			case 'f':
				file.speed = (int)(file.speed * 0.8);
				time.it_value.tv_sec = file.speed;
				time.it_value.tv_usec = 0;	
				time.it_interval.tv_sec = file.speed;
				time.it_interval.tv_usec = 0;

				setitimer(ITIMER_REAL, &time, NULL);
				printf("\033[7mScrolling faster: %d seconds.\n\033[0m", file.speed);
				
				fflush(stdout);
				break;
			case 's':
				file.speed  = (int)(file.speed + 1);
				time.it_value.tv_sec = file.speed;
				time.it_value.tv_usec = 0;	
				time.it_interval.tv_sec = file.speed;
				time.it_interval.tv_usec = 0;

				setitimer(ITIMER_REAL, &time, NULL);
				printf("\033[7mScrolling slower: %d seconds.\n\033[0m", file.speed);
				fflush(stdout);
				break;
			default:
				break;
		}
		
	}
	

	return 0;
}

//Function to display a page worth of data. 
void screenFull(int page){

	int LINELEN = 256;
	char  line[LINELEN];
	int i = page;
	while(fgets(line, LINELEN, file.fp)){

		if(fputs(line, stdout) == '\0'){
			fflush(stdout);
			printf("\033[7mEnd Of File\n");
			exit(1);
		}
		if((i - 3) < 0){
			fflush(stdout);
			break;
		}
		--i;
		
	}printf("\033[7mEnter to start/stop scrolling, space to page or 'q' to quit\n\033[0m");
}
//simple single line data display. 
void singleLine(){
	int LINELEN = 256;
	char  line[LINELEN];

	fgets(line, LINELEN, file.fp);
	if(fputs(line, stdout) == EOF){
			fflush(file.fp);
			printf("End Of File\n");
			exit(1);
		}
}

//Bad function name. Opens the file.
void fileToBuffer(char *filename){

	int LINELEN = 256;
	char  line[LINELEN];

	if(filename == NULL){
		perror("No File Found!\n");
		exit(1);
	}

	file.fp = fopen(filename, "r");
	if(file.fp == NULL){
		printf("File not found!\n");
		exit(1);
	}
	fseek(file.fp, 0L, SEEK_END);
	file.fileSize = ftell(file.fp);
	fseek(file.fp, 0L, SEEK_SET);

	//file.buf = (char *)malloc(file.fileSize + 1);
	//fread(file.buf, sizeof(char), file.fileSize, file.fp);
	//file.buf[file.fileSize] = '\0';
	//fclose(file.fp);

	file.lineSpot = 0;
	file.repeatLine = 0;
	file.speed = 5;
}
