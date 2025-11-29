/* Ncurses File Explorer + XOR encryption demo */
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "core.h"
#include "GUI.h"
#include "xorencryption.h"

#define MAX_PASSWORD_LEN 32
#define BUFFER_SIZE 1024 //read blocks

/* compile: gcc core.c main.c -lncurses -o fileexplorer */

// Prototypes
static void free_file_list(file_info* head);
file_info* menu_navigation(file_info* head, unsigned int fileCount, WINDOW* window);
int action_menu(file_info* targetFile, char* encryptionPassword, WINDOW* subWindow);

int encrypt(file_info* file, char* password){
	char tempFilePath[MAX_PATH_LEN];
	unsigned char buffer[BUFFER_SIZE];
	FILE* outputFile;
	FILE* inputFile;
	size_t n = 0;

	int selection = atoi(password);

	if (selection < 1 || selection > NUM_PRIMES){
		return -1;
	}

	int prime = PRIMES[selection -1];

	inputFile = fopen(file->filename, "rb");

	if (inputFile == NULL) {
		return -1;
	}
	snprintf(tempFilePath, sizeof(tempFilePath), "%s.enc", file->filename);
	outputFile = fopen(tempFilePath, "wb");
	if(outputFile == NULL){
		fclose(inputFile);
		return -1;
	}

	while ((n = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0){
		xor_with_prime(buffer, n, prime);
		fwrite(buffer, 1, n, outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);

	remove(file->filename);
	rename(tempFilePath, file->filename);
	return 0;
}

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
	WINDOW* subWindow;
	char encryptionPassword[MAX_PASSWORD_LEN];
	char titleString[512];
	sprintf(titleString,"Simple File Explorer and file encryptor | Active Directory:%s (q to quit)\n",dirpath);
	char subtitleString[] = "Use up and down arrow keys to navigate. Press Enter to encrypt/decrypt selected file.\n";
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
	gui_init();
	subWindow = newwin(SUB_WINDOW_HEIGHT, SUB_WINDOW_WIDTH,
				(LINES-SUB_WINDOW_HEIGHT)/2, (COLS-SUB_WINDOW_WIDTH)/2);
	keypad(subWindow,TRUE);
	wbkgd(subWindow, COLOR_PAIR(CP_SUBWINDOW));
	box(subWindow, 0,0);
	wrefresh(subWindow);

    while (1)
    {
        mvprintw(LINES/8,(COLS - strlen(titleString))/2,titleString);
        mvprintw((LINES/8)+1,(COLS - strlen(subtitleString))/2,subtitleString);
        selectedFile = menu_navigation(headNode, count, subWindow);			// Returns selected file (node)
		
		if(selectedFile == NULL)
		{
			endwin();
			return 0;
		}
		
		if(action_menu(selectedFile, encryptionPassword, subWindow) == 1)
		{
			switch(selectedFile->action)
			{
				case 'e':
					encrypt(selectedFile, encryptionPassword); // Run encryption function on file
					break;
				case 'd':
					encrypt(selectedFile, encryptionPassword); // Run decryption function on file
					break;				
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

// Blocking function
file_info* menu_navigation(file_info* head, unsigned int fileCount, WINDOW* window)
{
	int keypress;
	int i = 0;
	int y = 2;
	unsigned int pos = 0;
	int maxY = 0;
	file_info* currentFile = head;
	wclear(window);
	box(window,0,0);
	refresh();
	wrefresh(window);				// Set focus to window before enabling cursor
	while(currentFile->number != -1 && i < 10)
	{
		mvwprintw(window,y,2, "%d) %s", i, currentFile->filename);
		currentFile = currentFile->next;
		wrefresh(window);
		++i;
		++y;
	}
	maxY = getmaxy(window);
	mvwprintw(window, maxY-2, 1, "Prev 10 Files: Left Arrow | Next 10 Files: Right Arrow");
	y = 2;
	curs_set(2);
	wmove(window,y,2);
	wrefresh(window);
	while(1)
	{
		keypress = wgetch(window);
		switch(keypress)
		{
			case KEY_UP:
				if(pos == 0)
				{
					pos = 0;
				} else {
					--pos;
					--y;
				}
				break;
			case KEY_DOWN:
				if(pos == fileCount-1)
				{
					pos = fileCount-1;
				} else {
					++pos;
					++y;
				}
				break;
			case KEY_ENTER:
			case '\n':
				currentFile = head;
				while(currentFile->number != pos)
					currentFile = currentFile->next;
				return currentFile;
				break;
			case KEY_LEFT:
				break;
			case KEY_RIGHT:
				break;
			case 'q':
				return NULL;
			default:
				// Do nothing
		}
#if 0
		mvwprintw(window,1,10, "Y:%d | POS: %d", y, pos);
#endif
		wmove(window,y,2);
		wrefresh(window);
	}
	return NULL; // if we get here, there is an error
}

// Blocking function
int action_menu(file_info* targetFile, char* encryptionPassword, WINDOW* menuWindow)
{
	int choice;
	char password[MAX_PASSWORD_LEN];

	wclear(menuWindow);
	box(menuWindow, 0,0);
	wrefresh(menuWindow);
	mvwprintw(menuWindow, 1, 2, "Selected: %s", targetFile->filename);
	mvwprintw(menuWindow, 2, 2, "e - Encrypt | d - Decrypt | c - Cancel");
	wrefresh(menuWindow);

	while(1)
	{
		choice = wgetch(menuWindow);
		if (choice == 'e' || choice == 'd')
		{
			echo();
			curs_set(2);
			mvwprintw(menuWindow, 4, 2, "Prime ID (1-7): ");
			wclrtoeol(menuWindow);

			mvwgetnstr(menuWindow, 4, 18, password, sizeof(password)-1);
			noecho();
			wrefresh(menuWindow);

			targetFile->action = choice;		// So we can keep track of what we're doing to the file
			strcpy(encryptionPassword, password);
			return 1;
		} else if (choice == 'c') {
			return 0;
		} else if (choice == 'q') {
			endwin();
			exit(0);
		} else {
			mvwprintw(menuWindow, 4, 2, "Invalid Selection - Returning to the Main Menu");
			wrefresh(menuWindow);
			napms(2000);
			mvwprintw(menuWindow, 4, 2, "                          ");			
			wrefresh(menuWindow);
		}
	}
}

static void free_file_list(file_info* head)
{
    file_info* currentFile = head;
	file_info* tmp;
    while(currentFile != NULL)
    {
        tmp = currentFile->next;
		free(currentFile);
		currentFile = tmp;
    }
}
