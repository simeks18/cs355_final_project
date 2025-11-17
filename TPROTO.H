//Library prototypes

#include <keyboard.h>
#include <ascii.h>
#include <tstruct.h>


//Disk routine

long freeUpThedisk(void);
DISKSTATS *diskinfo(DISKSTATS *);
int getdrive(void);
void setdrive(int);

//String routine
void delete_Char(char *);
int find_Char(int, char *);
void insert_Char(char *, char);
void insertNum(char *, int);
void stringCJust(char *);
void stringEnul(char *);
void stringLjust(char *);
void stringRjust(char *);
void stringAnalysis(int *, int *, char *);

//Keyboard routines 
char getChar(void);
int getKey(void);
char getScan(void);
int getKeyboardStatus(void);
int getKeyboardFlag(void);
int inputFloat(float *, int);
int inputNumber(long *, int);
int prompt(char *, int);

//cursor routine

void getCursor(int *, int *);
void moveCursor(int, int);
void removeCursor(int, int);
void offCursor(void);
void onCursor(void);
void ssizeCursor(void);
void sizeCursor(int, int);
void setCursorLocation(void);
void readCursorLocation(void);

//Rectangle routines

//input parameters
RECTANGLE *setRectangle(RECTANGLE *, int, int, int, int);
void addRect(RECTANGLE *, RECTANGLE );
void subtractRect(RECTANGLE *, RECTANGLE *);
void duplicateRect(RECTANGLE *, RECTANGLE *);
void clearRect(RECTANGLE *);
void fillRect(RECTANGLE *, int);
void saveRect(RECTANGLE *);
unsigned int sizeRect(RECTANGLE *);

//Sound routines

void beep(void);
void bleep(void);
void offSound(void);
void onSound(int);

//Print Routines

int printCharacter(int, char);
int printScreen(int);

//Screen Routines

void printLineR(char);
void printCarriageRLineR(void);
void printCarriageR(void);
void printString(char *);
int readChar(void);

//Screen Routines

void printChar(char);
void printCarriageRLineR(void);
void printLineR(void);
void printCarriageR(void);
void printString(char *);
int readChar(void);
void videoAttribute(int, int, int, int);
void videoChar(int, int, int);
void videoString(int, int, int, char *, char);
void videoWrite(int, int, int, char *, int);
void videoInit(void);
int videoReadChar(int, int);
void writeChara(char, int);
void videoHorizontal(int, int, int, int);
void videoVertical(int, int, int, int);

void saveScreen(void);
void resetScreen(void);

//Window Routines

void displayWindow(WINDOW *);
void destroyWindow(WINDOW *);
void readImage(WINDOW *);
void readWindow(WINDOW *);
void removeWindow(WINDOW *);
void screenClear(void);
void setAttribute(WINDOW *, int);
void setBorder(WINDOW *, int);
void setTitle(WINDOW *, char *);
void startWindow(WINDOW *);
unsigned int sizeImg(WINDOW *);
void wmvCursor(WINDOW *, int, int);
void wrBox(WINDOW *);
void wrIMG(WINDOW *);
void wrWind(WINDOW *);
void wrWind(WINDOW *);
void wrImg(WINDOW *);
void wvdAttr(WINDOW *);
void wvdHoriz(int, int, int, int);
void wvdVert(WINDOW *, int, int, int, int);
void wvdString(WINDOW *, int, int, int, char *, char);
void wvdWrite(WINDOW *, int, int, int, char *, int);
void wvrdChar(WINDOW *, int, int);

//MISC routines

int mkToken(int, int);
int mkAttr(int, int, int, int);
void ascup(int, int, int, int);
void gtMode(int *, int *, int *);
void ramSize(void);
void exit_bad(char *);

//Intervention Routines
//These have the syntax left as is

long getVec(int);
void setVec(int, long);
void setCE(void);
void set16(int, int, int, int);
void set9dos(int, int, int);
int tsrfind(int);
int dosfind(int);
int tsrremv(void);
int dosremv(void);
void tsr(int);
void tsr9(int);
void setPSvec(void);
void tsrps(int);
void tsrtime(int);
void setTimer(void);
void tsrgtime(void);
void setClock(int, int, int);


//Intervention routines with changed syntax
void DisplayError(void);
void EraseError(void);

