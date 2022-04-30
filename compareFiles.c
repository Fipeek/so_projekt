#include <stdlib.h>
#include <utime.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>

bool copyFile(char* sourcePath, char* destinationPath);
bool deleteFile(char* targetPath);
bool mapFile(char* sourcePath, char* destinationPath);

void compareFiles(char* sourceDirName, char* destinationDirName, size_t sizeLimit)
{
    DIR* sD;
    DIR* dD;
    sD = opendir(sourceDirName);
    dD = opendir(destinationDirName);
    struct dirent* sF;
    struct dirent* dF;
    char sourcePath[257];
    char destinationPath[257];
    bool IsFound = false;

    while ((dF = readdir(dD)) != NULL)
    {
        struct stat dFStats;
        IsFound = false;
        sprintf(destinationPath, "%s/%s", destinationDirName, dF->d_name);
        if (stat(destinationPath, &dFStats) == -1)
        {
            printf("Problem z plikiem o nazwie1: %s\n", destinationPath);
            continue;
        }

        if ((dFStats.st_mode & S_IFMT) == S_IFDIR)
        {
            continue;
        }
        else
        {
            while ((sF = readdir(sD)) != NULL)
            {
                struct stat sFStats;
                sprintf(sourcePath, "%s/%s", sourceDirName, sF->d_name);
                if (stat(sourcePath, &sFStats) == -1)
                {
                    printf("Problem z plikiem o nazwie2: %s\n", sourcePath);
                    continue;
                }
                if ((sFStats.st_mode & S_IFMT) == S_IFDIR) // pomijanie katalog�w
                {
                    continue;
                }
                else
                {
                    if (strcmp(dF->d_name, sF->d_name) == 0)
                    {
                        IsFound = true;
                    }
                }
            }
            rewinddir(sD);
            if (!IsFound) // jezeli nie ma w zrodłowym
            {
                deleteFile(destinationPath);
            }
        }
    }
    rewinddir(dD);

    while ((sF = readdir(sD)) != NULL)
    {
        struct stat sFStats;
        IsFound = false;
        sprintf(sourcePath, "%s/%s", sourceDirName, sF->d_name);
        if (stat(sourcePath, &sFStats) == -1)
        {
            printf("Problem z plikiem o nazwie1: %s\n", sourcePath);
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
                    printf("Problem z plikiem o nazwie2: %s\n", destinationPath);
                    continue;
                }
                //printf("%s %s\n", dF->d_name,ctime(&dFStats.st_mtime));
                if ((dFStats.st_mode & S_IFMT) == S_IFDIR) // pomijanie katalog�w
                {
                    continue;
                }
                else
                {
                    if (strcmp(sF->d_name, dF->d_name) == 0)
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

                sprintf(destinationPath, "%s/%s", destinationDirName, sF->d_name);
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
