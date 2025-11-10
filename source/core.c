#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* UNTESTED */

char get_file_information(char* path, char* filename, file_info* fileInfo)
{
	DIR* targetDirectory = null;
	dirent* currentEntry = null;
	stat statStruct = null;
	char fileFound = 0;
	char full_file_path[MAX_PATH_LEN + MAX_FILENAME_LEN];
	
	targetDirectory = opendir(path);
	
	// Finding the target file
	while(currentEntry = readdir(targetDirectory))
		if(strcmp(currentEntry->d_name, filename))
			fileFound = 1;
		
	if(fileFound == 1)
	{	
		sprintf(full_file_path, "%s/%s", path, filename);
		stat(full_file_path, &statStruct);
		strcpy(fileInfo->filename, currentEntry->d_name);
		fileInfo->mode = statStruct.st_mode;
		fileInfo->userID = statStruct.st_uid;
		fileInfo->groupID = statStruct.st_gid;
	} else {
		return -1;
	}
}