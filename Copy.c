#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <utime.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <string.h>
#include <linux/limits.h>

bool copyFile(char *sourcePath, char *destinationPath )
{
	
	int packetsRead;
	int packetsWritten;
	
	int buffSize = sizeof(char);
	char buffer[buffSize]; 	
	
	int sourceFD = open(sourcePath, O_RDONLY);
	int destinationFD = open(destinationPath, O_CREAT | O_WRONLY);
	
	int priority = LOG_INFO | LOG_DAEMON;
	
	fchmod(destinationFD, S_IRUSR | S_IWUSR);
	openlog(NULL, LOG_CONS , priority);
	
	if(sourceFD == (-1))
	{
		close(sourceFD);
		close(destinationFD);			
		
		
		return false;
	}
	else if(destinationFD == (-1))
	{
		close(sourceFD);
		close(destinationFD);
		
		return false;
	}
	while(packetsRead = read(sourceFD, buffer, buffSize))
	{	
		if(packetsRead == -1)
		{
			close(sourceFD);
			close(destinationFD);
			
			return false;
		}
		
		packetsWritten = write(destinationFD, buffer, buffSize);
			
		if(packetsWritten == -1)
		{
			close(sourceFD);
			close(destinationFD);
			
			return false;
		}
	}
	
	
	int sClose = close(sourceFD);
	int dClose = close(destinationFD);
	
	if(sClose == (-1) || dClose == (-1))
	{
		return false;
	}
	
	
	
	char logMessage[PATH_MAX + 100];
	strcat(sourcePath, logMessage);
	
	char *message = "został skopiowany pomyślnie.";
	
	strcat(message, logMessage);
	time_t currtime = time(NULL);
	char *currtimeS = ctime(time);
	 
	strcat(currtimeS, logMessage);
	
	syslog(priority, logMessage);
	closelog();
	return true;
}




