#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xor_crypt.h" //must be in the same directory
#include <errno.h>

int main (int argc, char *argv[]){
if (argc != 4){
for (int i = 0; i < NUM_PRIMES; i++){
printf(" %d. Prime %d\n", i + 1, PRIMES[i]);
}
return 1;
}

const char *input_file = argv[1];
const char *output_file = argv[2];
int myprime = atoi(argv[3]); // conver ASCII to integer
int prime = PRIMES[myprime -1]; //select a prime and subtract one bc array

//check for valid input -- should not be 0 or less than 1
if (myprime < 1 || myprime > NUM_PRIMES) {
return 1;
}

int prime = PRIMES[myprime -1];

//read input file 
FILE *fileinput = fopen(input_file), "read");
//if there is no file input
if (!fileinput, "sadie_error");
return 1;
}

FILE *fileoutput = fopen(output_file), "write");
if (!=fileoutput){
fclose(fin);
return 1;
}


unsigned char buffer[BUFFER_SIZE];
size_t bytesread;
size_t bytesProcessedSoFar;
printf("processing file in...%d byte blocks \n", BUFFER_SIZE);

while ((bytesread = fread(buffer, 1, BUFFER_SIZE, fileinput)) > 0) {

XORPrime(buffer, bytesread, prime, total_processed);

fwrite(buffer, 1, bytesread, ffileoutput);
total_processed = total_processed + bytesread;

return 0;
}
