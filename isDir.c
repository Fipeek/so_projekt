#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

  bool isDir(DIR *dir){
	if(dir!=NULL){
	return true;
	}
	return false;
}
