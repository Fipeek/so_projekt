#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

bool isDir(DIR *dir);
void compareFiles(char* sourceDirName, char* destinationDirName);
void compareAndDeleteFilesAndDir(char* sourceDirName, char* destinationDirName);
void compareAndCopyFilesAndDir(char* sourceDirName, char* destinationDirName);
void main(int argc, char *argv[])
{
	int sleepTime = 300, fileSize = 6000;
	bool isRPar = false;
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
	
	while ((option_value = getopt(argc, argv, "t:r:s")))
	{
		switch (option_value)
		{
		case 't':
			if (optarg != NULL)
			{
				sleepTime = atoi(optarg);
			}
			else
			{
				printf("Podaj czas spania razem z parametrem -t\n");
				exit(3);
			}
			break;
		case 'r':
			isRPar = true;
			break;
		case 's':
			if (optarg != NULL)
			{
				fileSize = atoi(optarg);
			}
			else
			{
				printf("Podaj rozmiar duzego pliku razem z parametrem -s\n");
				exit(4);
			}
			break;
		default:
			break;
		}
	}
	if (isRPar)
	{
		compareAndDeleteFilesAndDir(argv[1], argv[2]);
		compareAndCopyFilesAndDir(argv[1], argv[2], fileSize);
	}
	else
	{
		compareFiles(argv[1], argv[2], fileSize);
	}
	
	
}
