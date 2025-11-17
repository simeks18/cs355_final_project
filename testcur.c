#include <stdio.h>
#include "tproto.h"

void main(void);

void 
main()

{

printf("\033[2J\033[H");

int row, col, count;

for (row = 0, col = 0, count = 0; count < 22; row ++, col ++, count ++)
{
moveCursor(row, col);
printf("Sadie Simek");
}
}

