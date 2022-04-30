#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <linux/limits.h>

bool copyFile(char* sourcePath, char* destinationPath);
void copyRecursively(char* sourcePath, char* targetPath);
bool mapFile(char* sourcePath, char* destinationPath);
void compareAndCopyFilesAndDir(char* sourceDirName, char* destinationDirName, size_t sizeLimit)
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

	while ((sF = readdir(sD)) != NULL)
	{
		if (!strcmp(sF->d_name, ".") || !strcmp(sF->d_name, ".."))
		{
			continue;
		}
		struct stat sFStats;
		IsFound = false;
		IsDir = false;
		sprintf(sourcePath, "%s/%s", sourceDirName, sF->d_name);
		if (stat(sourcePath, &sFStats) == -1)
		{
			printf("Problem z plikiem o nazwie1: %s\n", sourcePath);
			continue;
		}

		if ((sFStats.st_mode & S_IFMT) == S_IFDIR)
		{
			IsDir = true;
		}
		while ((dF = readdir(dD)) != NULL)
		{
			if (!strcmp(dF->d_name, ".") || !strcmp(dF->d_name, ".."))
			{
				continue;
			}
			struct stat dFStats;
			sprintf(destinationPath, "%s/%s", destinationDirName, dF->d_name);
			if (stat(destinationPath, &dFStats) == -1)
			{
				printf("Problem z plikiem o nazwie2: %s\n", destinationPath);
				continue;
			}
			if ((dFStats.st_mode & S_IFMT) == S_IFDIR) // pomijanie katalog�w
			{
				if (IsDir && strcmp(sF->d_name, dF->d_name) == 0)
				{
					compareAndCopyFilesAndDir(sourcePath, destinationPath, sizeLimit);
					IsFound = true;
					break;
				}
				continue;
			}
			else
			{
				if (!IsDir && strcmp(sF->d_name, dF->d_name) == 0)
				{
					IsFound = true;
					if (difftime(sFStats.st_mtime, dFStats.st_mtime) != 0) // jezeli daty modyfikacji rozne
					{
						if (sFStats.st_size > sizeLimit)
						{
							mapFile(sourcePath, destinationPath);
						}
						else
						{
							copyFile(sourcePath, destinationPath);
							
						}
					}
				}
			}
		}
		rewinddir(dD);
		if (!IsFound) // jezeli nie ma w docelowym
		{
			char helpString[PATH_MAX];
			sprintf(helpString, "%s/%s", destinationDirName, sF->d_name);
			if (!IsDir)
			{
				if (sFStats.st_size > sizeLimit)
				{
					mapFile(sourcePath, helpString);
				}
				else
				{
					copyFile(sourcePath, helpString);
				}
			}
			else
			{
				copyRecursively(sourcePath, helpString);
			}
		}
	}
	rewinddir(sD);
}
