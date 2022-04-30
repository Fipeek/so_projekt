#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <time.h>

bool deleteFile(char *targetPath)
{
	int priority = LOG_INFO | LOG_DAEMON;
	openlog(NULL, LOG_CONS , priority);
	
	if ( unlink(targetPath) == 0)
	{ 

		char logMessage[PATH_MAX + 100];
		
		time_t currtime = time(NULL);
		char *currtimeS = ctime(&currtime);
		
		sprintf(logMessage, "Plik %s został usunięty pomyślnie %s.", targetPath, currtimeS);
	
		syslog(priority, logMessage);
		closelog();
		
		return true;
	}
    	else 
    	{
		return false;
	}
}

