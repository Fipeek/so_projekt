#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

bool isDir(DIR *dir);


void main(int argc, char *argv[])
{
	DIR *sourceDir = opendir(argv[1]);
	DIR *destinationDir = opendir(argv[2]);
	if(!isDir(sourceDir)){
	printf("plik źródłowy nie jest katalogiem\n");
	}
	if(!isDir(destinationDir)){
	printf("plik docelowy nie jest katalogiem\n");
	}
	
}
