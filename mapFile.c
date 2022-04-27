#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>

bool mapFile(char* sourcePath, char* destinationPath)
{
    int sourceFile, destinationFile;
    char* source;
    char* destination;
    size_t fileSize;

    sourceFile = open(sourcePath, O_RDONLY);
    fileSize = lseek(sourceFile, 0, SEEK_END);
    source = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, sourceFile, 0);

    destinationFile = open(destinationPath, O_RDWR | O_CREAT, 0666);
    ftruncate(destinationFile, fileSize);
    destination = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, destinationFile, 0);

    if (source == (void*)-1)
        return false;

    if (destination == (void*)-1)
        return false;

    memcpy(destination, source, fileSize);

    munmap(source, fileSize);
    munmap(destination, fileSize);

    close(sourceFile);
    close(destinationFile);
    return true;
}
