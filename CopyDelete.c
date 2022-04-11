#include <stdio.h>
#include <sys/stat.h>



void copyFile(char *sourcePath, char *targetPath, bool)
{
	
	char oneBitBuffor;
   	FILE *sourceFile = fopen(sourcePath, "r");
   	FILE *targetFile = fopen(targetPath, "w");
  
	while( (oneBitBuffor = fgetc(sourceFile) ) != EOF )
		fputc(oneBitBuffor, targetFile);
   	  
}

void deleteFile(char *targetFile)
{
	if ( remove(targetFile) == 0) 
    	    printf("The file is deleted successfully.");
    	 
    	else 
    	    printf("The file is not deleted.");
}

