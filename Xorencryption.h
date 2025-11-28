#ifndef XORENCRYPTION_H
#define XORENCRYPTION_H

#include <stdio.h>
#include <stdlib.h> /for general utility functions
#include <string.h>
#include <errno.h>

//define prime constants (every 4th prime from the first 25)
int PRIMES[] = {2, 11, 23, 41, 59, 73, 97};
int NUM_PRIMES = 7;

//generate mask byte
void xor_with_prime(unsigned char *data, size_t length, int prime) {
        for (size_t i = 0, i < length; i++){
        unsigned char mask = (unsigned char)((i * prime) & 0xFF);
        data[i] = data[i] ^ mask; //XOR OPERATION with MASK
        }
}

