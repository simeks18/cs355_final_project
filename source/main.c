/* Ncurses Encryption Tool */

#include <stdio.h>
#include <stdlib.h>
#include <core.h>
#include <ncurses.h>

#define FILENAME argv[1]

/* UNTESTED */

int main(int argc, char* argv[])		
{
	/* Establishing Directory File List */
	file_info* fileNode;								// Head node
	get_directory_information(FILENAME, fileNode);
	int curX = 0;
	int curY = 0;
	int listPosition = 0;
	
	/* In final code we will init the GUI here. Best to test this all in the console first */
	/* Dar you should write the GUI init code for this section 
		1. Init the GUI
		2. Position the cursor somewhere in the middle of the screen
		3. Print the name of the program 
		4. Move the curser down */
		
	// Printing all the filenames of the directory we've passed in
	getyx(stdscr, curX, curY);		// Getting where we started at the top of this list
	while(fileNode->number >= 0) // TODO should probably create a check to prevent a large list
	{
		sprintf("%d. %s\n", fileNode->number, fileNode->filename);
		addstr(fileNode->filename);
		fileNode = fileNode->next;
	}
	move(curX, curY);					// Moving the cursor back to the top of the list
	
	while(1)
	{
		/* At this point we wait here and handle key presses 
		   up and down will navigate through the list. Pressing enter will 
		   bring up another screen that gives the option to encrypt or decrypt the file */
	}

	
	endwin();
	// TODO Read the system file and possibly implement a check
	
	// INIT GUI and prompt for password
	
	/* GUI Starts on same directory as executable. We can use a linked list of file_info structs 
	   to store all of the file information for the directory. Key presses will move the linked 
	   list currentNode pointer up and down through the list. Pressing enter will bring up a menu 
	   for that file where you can encrypt or decrypt the data*/
}