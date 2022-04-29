#include <stdio.h> 
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

void copyRecursively(char *sourcePath, char *targetPath);

int main(int argc, char *args[])
{

	copyRecursively(args[1],args[2]);

}

bool copyFile(char *sourcePath, char *targetPath);
void copyRecursively(char *sourcePath, char *targetPath)
{
	DIR *sourceDir = opendir(sourcePath);
	
	
	if(mkdir(targetPath, S_IRWXU) != 0)
	{
		printf("Problem ze stworzeniem katalogu %s", targetPath);
		return;
	}
	
	DIR *targetDir = opendir(targetPath);
	struct dirent *dir;
	if(sourceDir)
	{
		while((dir = readdir(sourceDir)) != NULL)
		{	
			if(!strcmp(dir->d_name, "."))
			{
				continue;
			}
			else if(!strcmp(dir->d_name, ".."))
			{
				continue;
			}
			else if(dir->d_type == 4)
			{
				char targetFilename[PATH_MAX];
				sprintf(targetFilename, "%s/%s", targetPath, dir->d_name);
				
				
				char sourceFilename[PATH_MAX];
				sprintf(sourceFilename, "%s/%s", sourcePath, dir->d_name);
				
				
				copyRecursively(sourceFilename, targetFilename);
			}
			else
			{
				char targetFilename[PATH_MAX];
				char sourceFilename[PATH_MAX];
				sprintf(sourceFilename, "%s/%s", sourcePath, dir->d_name);
				sprintf(targetFilename, "%s/%s", targetPath, dir->d_name);
				copyFile(sourceFilename, targetFilename);
			} 
		}
	}
}
