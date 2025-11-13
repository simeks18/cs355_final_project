#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILENAME_LEN 255			// 
#define MAX_PATH_LEN 255				// both of these are likely to change
#define FILETYPE_LEN 35				


// DataTypes
typedef struct 
{
	char filename[MAX_FILENAME_LEN];
	char fileLocation[MAX_PATH_LEN];
	char filetype[FILETYPE_LEN];
	int userID;
	int groupID;
	int mode;
	int number;
	file_info* nextFile; 
	
	// TODO probably should add fields for timestamp and hardlink count
}file_info;

// Function Prototypes

// One stop shop to get file information. Returns -1 on failure
char get_file_information(char* path, char* filename, file_info* fileInfo);
void get_directory_information(char* path, file_info* fileNode);