#include <string.h>
#include <stdio.h> 
#include <dirent.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>


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
				deleteRecursively(filename);
			}
			else
			{
				char filename[PATH_MAX];
				sprintf(filename, "%s/%s", pathname, dir->d_name);
				deleteFile(filename);
			} 
			
		}
		
		
		if(rmdir(pathname) ==0 )
		{
			char logMessage[PATH_MAX + 100];
		
			time_t currtime = time(NULL);
			char *currtimeS = ctime(&currtime);
			
			sprintf(logMessage, "Plik %s został usunięty pomyślnie %s.", pathname, currtimeS);
		
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
