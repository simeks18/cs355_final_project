/* start of source file

* File Name: TSTRUCT.H

* Defines  Structures and definitions used by the library

*/

typedef struct {
int  upperLeftRow; //Upper left row
int upperLeftColumn; //Upper left column
int lowerRightRow;
int lowerRightColumn;
unsigned int img_size;
unsigned int far *img_pointer;
unsigned int far *wind_pointer;
int box_type;
int attribute;
int visible;
int top_offset;
int top_length;
int show_top;
int bot_offset;
int bot_length;
int show_bot;
char *t_title; // A pointer to the t title structure
char *b_title; // A pointer to the b title structure
} TEXTWINDOW;



//DISKINFO STRUCTURE

typedef struct {
unsigned char media_descriptor_byte;
unsigned int number_of_clusters_available;
unsigned int number_of_clusters_total;
unsigned int number_of_sectors_per_cluster;
unsigned int bytes_per_sector;
} DISKSTATS;

//VIDEO STRUCTURE 

typedef struct {
int mode; // video mode
int row_width;
int page; 
unsigned int far *scrn; // Pointer to the video RAM
} VIDEO;

//RECTANGLE STRUCTURE 

typedef struct {
int upperLeftRow;
int upperLeftColumn;
int lowerRightRow;
int lowerRightColumn;
unsigned int *image; //Pointer to screen image
} SCREENAREA;

//Cursor Location Structure
//Holds the row and column of the saved cursor location

typedef struct {
int row;
int col;
} CURSORLOCATION; 


//Define WRBOX.C
#define S_S_S_S 0
#define S_S_D_D 1
#define D_D_S_S 2
#define D_D_D_D 3

//Define MKATTR.c
//Define the foreground and background color into single byte attributes

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 3
#define BROWN 4
#define WHITE 5
#define NORMAL 6

#define ON_INTENSITY 8
#define OFF_INTENSITY 0

#define ON_BLINK 128
#define OFF_BLINK 0

//Define SCROLL int routines
#define SCROLLUP 6
#define SCROLLDOWN 7

//Define KB Shift status

#define RIGHT_SHIFT 1
#define LEFT_SHIFT 2
#define CTRL_PRESS 4
#define ALT_PRESS 8
#define SCROLL_LOCK 16
#define NUM_LOCK 32
#define CAPS_LOCK 64
#define INSERT_ON 128
