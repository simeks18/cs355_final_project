/* Ncurses File Explorer + XOR encryption demo */
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "core.h"


/* compile: gcc core.c main.c -lncurses -o fileexplorer */

// Prototypes
static void free_file_list(file_info* head);
file_info* menu_navigation(file_info* head, unsigned int fileCount);
int action_menu(file_info* targetFile, char* encryptionPassword);
int encrypt(file_info* file, char* password);

int main(int argc, char* argv[])
{
    if (argc < 2)
	{
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    const char* dirpath = argv[1];
    int highlight = 0;
    int count = 0;
    int row = 3;
    int idx = 0;
	char encryptionPassword[MAX_PASSWORD_LEN];
    file_info* headNode = get_directory_information(dirpath);
	file_info* currentFile = headNode;
	file_info* selectedFile = NULL;

	// Invalid Directory Test
    if (!headNode)
    {
        fprintf(stderr, "Failed to open directory: %s\n", dirpath);
        return 1;
    }

    // Getting the file count
    while(currentFile->number >= 0)
    {
		++count;
		currentFile = currentFile->next;
    }
    currentFile = headNode;


    // Starting the GUI Up...
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    while (1)
    {
        clear();
        mvprintw(0, 0, "Simple File Explorer | Active Directory:%s (q to quit)", dirpath);
        mvprintw(1, 0, "Use up and down arrow keys to navigate. Press Enter to encrypt/decrypt selected file.\n");
        selectedFile = menu_navigation(headNode, count);			// Returns selected file (node)
		if(selectedFile == NULL)
		{
			endwin();
			return 0;
		}
		if(action_menu(selectedFile, encryptionPassword) == 1)
		{
			switch(selectedFile->action)
			{
				case 'e':
					encrypt(selectedFile, encryptionPassword); // Run encryption function on file
				case 'd':
					encrypt(selectedFile, encryptionPassword); // Run decryption function on file
				default:
					; // No action to take place here
			}
			selectedFile->action = 0;								// Reset after doing the work
			encryptionPassword[0] = '\0';							// ...same
		} else {

		}
	}
    endwin();
    free_file_list(headNode);
    return 0;
}

// Encryption/Decryption Function - Returns -1 on failure
int encrypt(file_info* file, char* password)
{
	char tempFilePath[MAX_PATH_LEN];
    char buffer;
	FILE* outputFile;
	FILE* inputFile;
	size_t passlen;
	int i = 0;
	int n = 0;

	// Opening input file 
	inputFile = fopen(file->filename, "wb");				// Opening with write access so we can delete later
	if(inputFile == NULL)
	{
		// TODO Print an error message here
		exit(EXIT_FAILURE);
	}

	// Creating temporary file to work with
	snprintf(tempFilePath, sizeof(file->filename), "%s.enc", file->filename); //TODO needs error checking and overflow prevention
	outputFile = fopen(tempFilePath, "wb");
	if(outputFile == NULL)
	{
		// TODO Print an error message here
		exit(EXIT_FAILURE);
	}

	passlen = strlen(password);
	if(passlen == 0)
	{
		fclose(inputFile);
		fclose(outputFile);
		// TODO Print an error message
		return -1;
	}

	// Starting encryption/decryption
	while ((n = fread(&buffer, 1, 1, inputFile)) > 0) 
	{
        buffer ^= (unsigned char)password[(i) % passlen];		// note to Sadie: why use the offset? % passlen is very clever!
        //offset += n;
        fwrite(&buffer, 1, 1, outputFile) != n; 		// TODO need to check for errors
    }
	
	// Deleting the original file and replacing it with the encrypted version
	remove(file->filename);
	rename(tempFilePath,  file->filename);				// TODO needs error checking

	fclose(inputFile);
	fclose(outputFile);
	return 0;
}


// Blocking function
file_info* menu_navigation(file_info* head, unsigned int fileCount)
{
	int keypress;
	unsigned int pos = 0;
	file_info* currentFile = head;
	mvprintw(2, 0, "Selected File: %d/%d: %s", currentFile->number+1, fileCount, currentFile->filename);
	while(1)
	{
		keypress = getch();
		switch(keypress)
		{
			case KEY_DOWN:
				if(pos == 0)
					pos = 0;
				else
					--pos;
				break;
			case KEY_UP:
				if(pos == fileCount-1)
					pos = fileCount-1;
				else
					++pos;
				break;
			case KEY_ENTER:
			case '\n':
				currentFile = head;
				while(currentFile->number != pos)
					currentFile = currentFile->next;
				return currentFile;
				break;
			case 'q':
				return NULL;
			default:
				// Do nothing
		}
		currentFile = head;
		while(currentFile->number != pos)									// TODO def needs error handling
			currentFile = currentFile->next;
		move(2, 0);
		clrtoeol();
		mvprintw(2, 0, "Selected File: %d/%d: %s", currentFile->number+1, fileCount, currentFile->filename);
		refresh();
	}
	return NULL; // if we get here, there is an error
}

// Blocking function
int action_menu(file_info* targetFile, char* encryptionPassword)
{
	clear();
	int choice;
	char password[MAX_PASSWORD_LEN]; 
	WINDOW* menu = newwin(7, 60, 4, 10);
	box(menu, 0, 0);
	mvwprintw(menu, 1, 2, "Selected: %s", targetFile->filename);
	mvwprintw(menu, 2, 2, "e - Encrypt    d - Decrypt    c - Cancel");
	mvwprintw(menu, 4, 2, "Enter choice: ");
	wrefresh(menu);
	while(1)
	{
		choice = wgetch(menu);
		if (choice == 'e' || choice == 'd') 
		{
			// prompt for password 
			echo();
			curs_set(1);
			mvwprintw(menu, 4, 2, "Password: ");
			wclrtoeol(menu);
			mvwgetnstr(menu, 4, 12, password, sizeof(password)-1);
			noecho();
			curs_set(0);
			refresh();
			targetFile->action = choice;		// So we can keep track of what we're doing to the file
			strcpy(encryptionPassword, password);
			delwin(menu);
			return 1;
		} else if (choice == 'c') {
			delwin(menu);
			return 0;
		} else {
			mvwprintw(menu, 4, 2, "Invalid Selection - Returning to the Main Menu");
			wrefresh(menu);
			napms(2000);
			delwin(menu);
			return -1;
		}
	}

}

static void free_file_list(file_info* head)
{
    file_info* currentFile = head;
	file_info* tmp;
    while(tmp)
    {
        tmp = currentFile->next;
		free(currentFile);
		currentFile = tmp;
    }
}
