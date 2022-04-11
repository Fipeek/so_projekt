#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void compareFiles(char* sourceDirName, char* destinationDirName)
{
	DIR* sD, dD;
	struct dirent* sF, dF;
	sD = opendir(sourceDirName);
	dD = opendir(destinationDirName);
	char* sourcePath[100];
	char* destinationPath[100];
	bool IsFound = false;
	while ((sF = readdir(sD)) != NULL)
	{
		struct stat sFStats;
		IsFound = false;
		sprintf(sourcePath, "%s/%s", sourceDirName, sF->d_name);
		if (stat(sourcePath, &sFStats) == -1)
		{
			printf("Problem z plikiem o nazwie: %s\n", sourcePath);
			continue;
		}

		if ((sFStats.st_mode & S_IFMT) == S_IFDIR)
		{
			continue;
		}
		else
		{
			while ((dF = readdir(dD)) != NULL)
			{
				struct stat dFStats;
				sprintf(destinationPath, "%s/%s", destinationDirName, dF->d_name);
				if (stat(destinationPath, &dFStats) == -1)
				{
					printf("Problem z plikiem o nazwie: %s\n", destinationPath);
					continue;
				}

				if ((dFStats.st_mode & S_IFMT) == S_IFDIR) // pomijanie katalogów
				{
					continue;
				}
				else
				{
					if (strcmp(sF->d_name, dF->d_name) == 0)
					{
						if (difftime(sFStats.st_mtime, dFStats.st_mtime) != 0) // jezeli daty modyfikacji rozne
						{
							//kopiowanie ze zrodlowego do docelowego
							IsFound = true;
						}
					}
				}
			}
			if (!IsFound) // jezeli nie ma w docelowym
			{
				//kopiowanie ze zrodlowego do docelowego
			}
		}
	}
}
