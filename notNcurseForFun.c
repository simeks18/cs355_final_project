#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>


//Return values for special keys
#define K_ESC 27
#define K_ARROW_UP 1000
#define K_ARROW_DOWN 1001
#define K_ARROW_LEFT 1002
#define K_ARROW_RIGHT 1003

#define ANSI_COLOR_PINK "\033[XXXm"


//Critical and ensure that the original settings can be reverted to
//Puts the terminal back to normal
struct termios orig_termios;

// --function prototypes 

void disable_raw_mode();
void enable_raw_mode();
int read_key();

//Terminal reset function
// This function MUST be called before the program exits or crashes.
void disable_raw_mode() {
    // TCSAFLUSH waits for output to be transmitted and discards pending input.
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        perror("There was an error disabling raw mode");
        exit(EXIT_FAILURE);
    }
}

// Terminal Setup Function
void enable_raw_mode() {
if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("Error strawberry milkshakes");
        exit(EXIT_FAILURE);
    }

//Register the reset function automatically when the terminal exits
if (atexit(disable_raw_mode) != 0) {
        perror("The Computer could not register reset function");
        exit(EXIT_FAILURE);
    }

struct termios raw = orig_termios;

//Safety feature #1 to allow Ctrl+C and Ctrl+Z to work  
raw.c_lflag &= ~(ICANON | ECHO);

raw.c_cc[VMIN] = 0; //Returns read immediately even if 0 bytes
raw.c_cc[VTIME] = 1; //100ms timeout for read() and this is imp. for escape sequence handling 

if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("Error bananasplits");
        exit(EXIT_FAILURE);
}
}

int read_key() {
	char c;

	// read attempts to read 1 byte and will return 0 after 100 ms if no key is pressed
if (read(STDIN_FILENO, &c, 1) == 0) {

return 0;
}

//check for the start of escape sequence where user would hit "control C"
if (c == K_ESC) {
char seq[3];

//read the next two bytes quickly and if the read times out, the escape key was not pressed 
if (read(STDIN_FILENO, &seq[0], 1) == 0) return K_ESC;
if (read(STDIN_FILENO, &seq[1], 1) == 0) return K_ESC;

if (seq[0] == '[') {

switch (seq[1]) {
case 'A': return K_ARROW_UP;
case 'B': return K_ARROW_DOWN;
case 'C': return K_ARROW_RIGHT;
case 'D': return K_ARROW_LEFT;

}}

//if not recognized key sequence 
return K_ESC;
}

//if std ascii key
return c;
}


int main() {
    printf("\033[31;1;4mPress CTR+C or 'q' to quit\033[0m\n");
    printf("Press Arrow Keys, ESC, and letter keys to see the output.\n");

    enable_raw_mode(); // Start Noncanonical Mode

    int key;
    while (1) {
        key = read_key();

        if (key != 0) { // Only print if a key was actually pressed (not a timeout)
            if (key == 'q') {
                printf("\n I quit \n");
                break;
            }

            switch (key) {
                case K_ARROW_UP:    printf("\n[UP ARROW Pressed] "); break;
                case K_ARROW_DOWN:  printf("\n[DOWN ARROW Pressed] "); break;
                case K_ARROW_LEFT:  printf("\n[LEFT ARROW Pressed] "); break;
                case K_ARROW_RIGHT: printf("\n[RIGHT ARROW Pressed] "); break;
                case K_ESC:         printf("\n[ESC Key Pressed] "); break;
                default:            printf("\n[Key: %c, Code: %d] ", (char)key, key);
            }
        }
    }

    // disable_raw_mode() is called automatically via atexit()
    printf("Terminal restored to normal mode.\n");
    return 0;
}
