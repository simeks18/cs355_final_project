#ifndef XORENCRYPTION_H
#define XORENCRYPTION_H

#include <stddef.h> 

//constants for prime number selection 
//use in the .C file
extern int PRIMES[];
extern int NUMPRIMES;

//function prototype
void XORprime(unsigned char *data, size_t length, int prime);

#endif //preprocessor director
