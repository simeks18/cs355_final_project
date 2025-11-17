// 
// MVCUR.c

//mvCUR(row, column)

// returns nothing


#include <stdio.h>
#include "tproto.h"

void moveCursor(int row,int column)
{
printf("\033[%d;%dH", row, column);

fflush(stdout);

}
