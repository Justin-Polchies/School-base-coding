#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <fcntl.h>

//Structs for the Archive file.
struct header {
    unsigned int uid;
    char owner[64];
    unsigned int files_tot;
};   

struct FileHeader {
    size_t size;
    time_t timestamp;
    char filename[256];
    unsigned int options;
};



//int checkForFile(int argc, char* argv[]); --> future feature
//void checkForDir(); --> future feature
void archive(int argc, char* argv[]);
void unarchive(int argc, char* argv[]);
void argCheck(int args);

int main(int argc, char* argv[]) {
    
    argCheck(argc);

    if (!(strcmp(argv[1], "c"))) {
        archive(argc, argv);
    }

    if (!strcmp(argv[1], "x")) {
	    unarchive(argc, argv);
    }

	return 0;
}

//Function to check how many argument are on the command line and if there isn't enought exits. future change to deal with the missing option.
void argCheck(int args){

    if(args < 2){
        
        printf("Please include either c or z after your calling zarchiver!\n");
        exit(0);
    }
}

//unused function. Possible usage in a future update.
void checkForDir() {
    struct stat dir = { 0 };

	char *cd;
	cd = getcwd(NULL,0);
	
	strcat(cd,"/archive");
	printf("%s\n",cd);

    if (stat(cd, &dir) == -1) {
        mkdir(cd, 777);
    }

    
}

//The function to archive files. Future updates will allow directory change but for now places the archive file in current directory.
void archive(int argc, char* argv[]) {

    uid_t idn;
    struct header h;
    idn = geteuid();
    struct passwd *pw = getpwuid(idn);
    strcpy(h.owner, pw->pw_name);

    int n, totalfiles;
    char line[128], temp[3],arcname[25];
    struct dirent** files;
    FILE *fp;


    printf("The Following is a list of files found in the Current Directory.\n");
    printf("\n");

    n = scandir(getcwd(NULL, 0), &files, NULL, alphasort);

    while ((n--)) {

        printf("%s\n", files[n]->d_name);
        free(files[n]);
    }
    printf("How many files would you like to archive today?\n");
    fgets(temp, sizeof(temp), stdin);
    totalfiles = atoi(temp);
    if(totalfiles == 0){ exit(0);}
    h.files_tot = totalfiles;

    struct FileHeader fh[totalfiles];

	FILE *fwr;
    
	if(argc <= 2){
        printf("What would you like to call this archive?\n");
        fgets(arcname, sizeof(arcname), stdin);
        strtok(arcname, "\n");
        strcat(arcname, ".z");

		while(access(arcname, F_OK) == 0){
            printf("File already exist. Please Pick a new Name?\n");
		    fgets(arcname, sizeof(arcname), stdin);
		    strtok(arcname, "\n");
		    strcat(arcname, ".z");
        }
	}
	
    if (arcname != NULL) {
        fwr = fopen(arcname, "wb");
	    fprintf(fwr, "%d\n %s\n %d\n", h.uid, h.owner, h.files_tot);
    }
   

    for (int i = 0; i < totalfiles; i++) {
        printf("What File you want to archive?.\n");
        fgets(line, sizeof(line), stdin);
	    strtok(line, "\n");

        fp = fopen(line, "r");

	    while(fp == NULL){
            printf("NO FILE FOUND!!!!!!\n");
            printf("What File you want to archive?\n");
            fgets(line, sizeof(line), stdin);
            strtok(line, "\n");
            fp = fopen(line, "r");
            
        }

        fseek(fp, 0, SEEK_END);
        fh[1].size = ftell(fp);
        strcpy(fh[1].filename, line);
        fh[1].timestamp = time(0);
	    fseek(fp, 0, SEEK_SET);
	    //fwrite (&fh, sizeof(struct FileHeader), 1, fwr);
        fprintf(fwr, "%ld\n %ld\n %s", fh[1].size, fh[1].timestamp, fh[1].filename);

	    char ch;
	    ch = '\n';
        
	    while(ch != EOF){
		    fputc(ch, fwr);
		    ch = fgetc(fp);
	    }

        fputc(ch, fwr);
        
	    printf("\nFile %s was archived.\n", fh[1].filename);
        remove(fh[1].filename);       
    }
	
	fclose(fp);
	fclose(fwr);
}

//As the name states it takes in an archived file and unarchives it. It takes in a file as an argument from the CMD line.
void unarchive(int argc, char* argv[]) {

    int n, totalfiles;
    char line[256], temp[3],arcname[25];
    struct dirent** files;
    FILE *fp;
    struct FileHeader fh;

    // Old Place holder Message.
    // printf("We have been trying to reach you about your car warrenty.\n");

    if(argc < 3){
        printf("The Following is a list of files found in the Current Directory.\n");
        printf("\n");
    
        n = scandir(getcwd(NULL, 0), &files, NULL, alphasort);
    
        while ((n--)-2) {
    
            printf("%s\n", files[n]->d_name);
            free(files[n]);
        }
        printf("What File you want to unarchive?\n");
        fgets(line, sizeof(line), stdin);
	    strtok(line, "\n");

        fp = fopen(line, "r");

	    while(fp == NULL){
            printf("NO FILE FOUND!!!!!!\n");
            printf("What File you want to unarchive?\n");
            fgets(line, sizeof(line), stdin);
            strtok(line, "\n");
            fp = fopen(line, "r");
        }

        fgets(line, sizeof(line), fp);
        fgets(line, sizeof(line), fp);
        totalfiles = atoi(fgets(line, sizeof(line), fp));
        
        printf("Total files Unarchived -> %d\n", totalfiles);
        int i = 0;

        //A while loop to get the files name and create a new file for the contents. 
        //the inner while will read in the content for that file.
        //Uses the totalfiles value to know how many files.
        while(i < totalfiles){
            fh.size = atoi(fgets(line, sizeof(line), fp));
            fgets(line, sizeof(line), fp);
            strcpy(fh.filename, fgets(line, sizeof(line), fp));
            i++;
            FILE *newFile = fopen(fh.filename,"wb");
            
            char ch = fgetc(fp);

            while(ch != EOF){
                fputc(ch, newFile);
                ch = fgetc(fp);
                
            }
            
            fclose(newFile);
        }
        fclose(fp);
        //remove(line);
    }else{

        fp=fopen(argv[2],"r");
        if(fp == NULL){
            printf("failed to open!!\n");
            exit(0);
        }else{
            printf("File Opened.\n");
        }

        //deals with unused strings for now.
        fgets(line, sizeof(line), fp);
        fgets(line, sizeof(line), fp);
        totalfiles = atoi(fgets(line, sizeof(line), fp));
        
        printf("Total files Unarchived -> %d\n", totalfiles);
        int i = 0;

        //A while loop to get the files name and create a new file for the contents. 
        //the inner while will read in the content for that file.
        //Uses the totalfiles value to know how many files.
        while(i < totalfiles){
            fh.size = atoi(fgets(line, sizeof(line), fp));
            fgets(line, sizeof(line), fp);
            strcpy(fh.filename, fgets(line, sizeof(line), fp));
            i++;
            FILE *newFile = fopen(fh.filename,"wb");
            
            char ch = fgetc(fp);

            while(ch != EOF){
                fputc(ch, newFile);
                ch = fgetc(fp);
                
            }
            
            fclose(newFile);
        }
        
        remove(argv[2]);
        fclose(fp);
    }
    
}


