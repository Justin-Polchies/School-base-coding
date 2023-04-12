#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

#define MAXBUF 250000

int main() {
	char name[125];

	fileOpener();

	return 0;
}

void fileOpener() {

	FILE* fp;
	char* buf = 0;
	int filesize;

	if (fp) {

		fseek(fp, 0, SEEK_END);
		filesize = ftell(fp);
		printf("%d", filesize);

		buf = malloc(filesize);
		if (buf) {
			fread(buf, 1, filesize, fp);

		}
		printf(" %.*s", len, buf);

		fclose(fp)

	}

}
