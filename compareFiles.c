#include <stdlib.h>
#include <utime.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>

bool copyFile(char* sourcePath, char* targetPath);
bool deleteFile(char* targetFile);

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
                //printf("%s %s\n", dF->d_name,ctime(&dFStats.st_mtime));
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
                                if (mapFile(sourcePath, destinationPath))
                                {
                                    printf("Kopiowanie pliku %s zakończone pomyślnie", sF->d_name);
                                }
                                else
                                {
                                    printf("niepoprawne skopiowanie pliku \n");
                                }
                            }
                            else
                            {
                                if (copyFile(sourcePath, destinationPath))
                                {
                                    printf("\n poprawne skopiowanie pliku \n");
                                    struct utimbuf targetTime;

                                    targetTime.actime = sFStats.st_atime;
                                    targetTime.modtime = sFStats.st_mtime;

                                    if (utime(destinationPath, &targetTime) == 0)
                                    {
                                        printf("git zmiana");
                                    }

                                }
                                else
                                {
                                    printf("niepoprawne skopiowanie pliku \n");
                                }
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
                    if (mapFile(sourcePath, destinationPath))
                    {
                        printf("Kopiowanie pliku %s zakończone pomyślnie", sF->d_name);
                    }
                    else
                    {
                        printf("niepoprawne skopiowanie pliku \n");
                    }
                }
                else
                {
                    if (copyFile(sourcePath, destinationPath))
                    {
                        printf("\n poprawne skopiowanie pliku \n");
                        struct utimbuf targetTime;

                        targetTime.actime = sFStats.st_atime;
                        targetTime.modtime = sFStats.st_mtime;

                        if (utime(destinationPath, &targetTime) == 0)
                        {
                            printf("git zmiana");
                        }

                    }
                    else
                    {
                        printf("niepoprawne skopiowanie pliku \n");
                    }
                }
            }
        }
    }
}
