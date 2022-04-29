#include <unistd.h>
#include <stdio.h>

bool deleteFile(char *targetPath)
{
	if ( unlink(targetPath) == 0)
	{ 
    		printf("%s plik usunięty pomyślnie.\n\n", targetPath);
	}
    	else 
    	{
    		printf("%s błąd w usuwaniu pliku. Sprawdz błędy.", targetPath);
		return false;
	}
}

