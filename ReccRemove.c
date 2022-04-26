
#include <string.h>
#include <stdio.h> 
#include <dirent.h>
#include <stdbool.h>
#include <linux/limits.h>

void deleteReccursively(char *pathname);
bool deleteFile(char *targetFile);

int main(int argc, char *args[])
{
	deleteReccursively(args[1]);
}

void deleteReccursively(char *pathname)
{
	DIR *d = opendir(pathname);
	struct dirent *dir;

	if(d)
	{
		while((dir = readdir(d)) != NULL)
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
				char filename[PATH_MAX];
				sprintf(filename, "%s/%s", pathname, dir->d_name);
				deleteReccursively(filename);
			}
			else
			{
				char filename[PATH_MAX];
				sprintf(filename, "%s/%s", pathname, dir->d_name);
				printf("%s %d file is  deleted \n", filename, dir->d_type);
				deleteFile(filename);
			} 
			
		}
		
		printf("%s directory is deleted \n", pathname);
		deleteFile(pathname);
			
	}
}
