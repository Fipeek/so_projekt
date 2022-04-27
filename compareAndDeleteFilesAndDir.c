#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <linux/limits.h>
void compareAndDeleteFilesAndDir(char* sourceDirName, char* destinationDirName)
{
	DIR* sD;
	DIR* dD;
	sD = opendir(sourceDirName);
	dD = opendir(destinationDirName);
	struct dirent* sF;
	struct dirent* dF;
	char sourcePath[PATH_MAX];
	char destinationPath[PATH_MAX];
	bool IsFound = false;
	bool IsDir = false;
	while ((dF = readdir(dD)) != NULL)
	{
		if (!strcmp(dF->d_name, ".") || !strcmp(dF->d_name, ".."))
		{
			continue;
		}
		struct stat dFStats;
		IsFound = false;
		IsDir = false;
		sprintf(destinationPath, "%s/%s", destinationDirName, dF->d_name);
		if (stat(destinationPath, &dFStats) == -1)
		{
			printf("Problem z plikiem o nazwie1: %s\n", destinationPath);
			continue;
		}

		if ((dFStats.st_mode & S_IFMT) == S_IFDIR)
		{
			IsDir = true;
		}
		while ((sF = readdir(sD)) != NULL)
		{
			if (!strcmp(sF->d_name, ".") || !strcmp(sF->d_name, ".."))
			{
				continue;
			}
			struct stat sFStats;
			sprintf(sourcePath, "%s/%s", sourceDirName, sF->d_name);
			if (stat(sourcePath, &sFStats) == -1)
			{
				printf("Problem z plikiem o nazwie2: %s\n", sourcePath);
				continue;
			}
			if ((sFStats.st_mode & S_IFMT) == S_IFDIR) 
			{
				if (IsDir && strcmp(dF->d_name, sF->d_name) == 0)
				{
					compareAndDeleteFilesAndDir(sourcePath, destinationPath);
					IsFound = true;
					break;
				}
				continue;
			}
			else
			{
				if (!IsDir && strcmp(dF->d_name, sF->d_name) == 0)
				{
						IsFound = true;
						break;
				}
			}
		}
		rewinddir(sD);
		if (!IsFound) // jezeli nie ma w zrodłowym
		{
			if (!IsDir)
				printf("usuwanie pliku o nazwie: %s\n", destinationPath);
				//deleteFile(destinationPath);
			else
				printf("usuwanie folderu o nazwie: %s\n", destinationPath);
				//deleteDir(destinationPath);
		}
	}
}
