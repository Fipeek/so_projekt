
#include <string.h>
#include <stdio.h> 
#include <dirent.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <syslog.h>
#include <time.h>


bool deleteFile(char *targetPath);

int main(int argc, char *args[])
{
	deleteReccursively(args[1]);
}

void deleteRecursively(char *pathname)
{
	DIR *d = opendir(pathname);
	struct dirent *dir;
	
	int priority = LOG_INFO | LOG_DAEMON;
	
	openlog(NULL, LOG_CONS , priority);

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
				printf("%s %d usunięto plik \n", filename, dir->d_type);
				deleteFile(filename);
			} 
			
		}
		
		
		if(rmdir(pathname) ==0 )
		{
			char logMessage[PATH_MAX + 100];
		
			time_t currtime = time(NULL);
			char *currtimeS = ctime(&currtime);
			
			sprintf(logMessage, "Plik %s został usunięty pomyślnie %s.", targetPath, currtimeS);
		
			syslog(priority, logMessage);
			closelog();
		}
		else
		{
			return;
		}
		
		
	}
	else
	{
		return;
	}
}
			
