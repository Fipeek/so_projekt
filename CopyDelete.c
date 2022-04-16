#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

int main()
{}

bool copyFile(char *sourcePath, char *targetPath)
{
	int numberOfPackets = 1;
	int buffSize = sizeof(char);
	int packetsRead;
	char buffer[buffSize]; 
	
   	FILE *sourceFile = fopen(sourcePath, "r");
   	FILE *targetFile = fopen(targetPath, "w");
  	
  	if(!sourceFile)
  		return false;
	if(!targetFile)
		return false;
  
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
   	 
 	fclose(targetFile);
	fclose(sourceFile);
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
