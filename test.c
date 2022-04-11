#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h> 
#include <time.h>
#include <string.h>
#include <sys/types.h>
void printFiles(DIR *sourceDir, DIR *destinationDir){
struct dirent *dir;
struct dirent *dir2;
struct stat filestat;
struct stat filestat2;
int i=0;
	while((dir = readdir(sourceDir)) != NULL){
			 stat(dir->d_name,&filestat);	
			// printf("%s  ", dir -> d_name);
			// printf(" File modify time PIERWSZY PLIK %s",ctime(&filestat.st_mtime));	
            
                while((dir2 = readdir(destinationDir)) != NULL){
                 stat(dir2->d_name,&filestat2);	
                //  printf("%s  ", dir2 -> d_name);
                //  printf(" File modify time DRUGI PLIK %s",ctime(&filestat2.st_mtime));
                 if(strcmp(dir->d_name,dir2->d_name)==0 && difftime(filestat.st_mtime, filestat2.st_mtime) == 0){
                     printf("znalazlem taki sam plik\n");
                     printf("%s\n", dir->d_name);
                 }	
            }
            rewinddir(destinationDir);
		}
		
	    closedir(sourceDir);
 
}
 