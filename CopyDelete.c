#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <utime.h>


bool copyFile(char *sourcePath, char *targetPath)
{
	int numberOfPackets = 1;
	int buffSize = sizeof(char);
	int packetsRead;
	char buffer[buffSize]; 
	printf("%s\n", sourcePath);
	printf("%s\n", targetPath);
	
   	FILE *sourceFile = fopen(sourcePath, "r");
   	FILE *targetFile = fopen(targetPath, "w");
  	
  	if(!sourceFile)
  		return false;
	if(!targetFile)
		return false;
  	printf("\n Oba pliki poprawne");
  	
	while(packetsRead = fread(buffer, buffSize, numberOfPackets, sourceFile))
	{
		fwrite(buffer, sizeof(char), packetsRead, targetFile);
		if(feof(sourceFile))
			return true;
		if(ferror(sourceFile))
		{
			printf("Błąd w odczytywanie pliku.");
			return false;
		}
	}
   	printf("\nPrzed zamknieciem pliku \n");
   	
 	fclose(targetFile);
	fclose(sourceFile);
	return true;
}



bool deleteFile(char *targetFile)
{
	if ( remove(targetFile) == 0)
	{ 
    		printf("The file is deleted successfully.");
		return true;	 	
	}
    	else 
    	{
    		printf("The file is not deleted.");
		return false;
	}
}
