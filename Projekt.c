#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

bool isDir(DIR *dir);
void compareFiles(char* sourceDirName, char* destinationDirName, size_t sizeLimit);
void compareAndDeleteFilesAndDir(char* sourceDirName, char* destinationDirName);
void compareAndCopyFilesAndDir(char* sourceDirName, char* destinationDirName, size_t sizeLimit);
bool SleepMode(int sleepTime);
void main(int argc, char *argv[])
{
	daemon(1,0);
	int sleepTime = 300;
	int option_value = 0;
	size_t fileSize = 100000;
	bool isRPar = false;
	char sourceName[PATH_MAX], destinationName[PATH_MAX];
	strcpy(sourceName, argv[1]);
	strcpy(destinationName, argv[2]);
	DIR *sourceDir = opendir(argv[1]);
	DIR *destinationDir = opendir(argv[2]);
	if(!isDir(sourceDir)){
	printf("plik źródłowy nie jest katalogiem\n");
	exit(1);
	}
	if(!isDir(destinationDir)){
	printf("plik docelowy nie jest katalogiem\n");
	exit(2);
	}
	while ((option_value = getopt(argc, argv, ":t:s:r")) != -1)
	{
		switch (option_value)
		{
		case 't':
			sleepTime = atoi(optarg);
			break;
		case 'r':
			isRPar = true;
			break;
		case 's':
			fileSize = atoi(optarg);
			break;
		case ':': 
                	printf("Opcja potrzebuje wartości\n"); 
                	break; 
		case '?': 
                	printf("Nieznana opcja: %c\n", optopt);
                	break; 
		default:
			break;
		}
	}
	if (isRPar)
	{
		while(1)
		{
			SleepMode(sleepTime);
			compareAndDeleteFilesAndDir(sourceName, destinationName);
			compareAndCopyFilesAndDir(sourceName, destinationName, fileSize);
		}
	}
	else
	{
		while(1)
		{
			SleepMode(sleepTime);
			compareFiles(sourceName, destinationName, fileSize);
		}
	}
	
	
}
