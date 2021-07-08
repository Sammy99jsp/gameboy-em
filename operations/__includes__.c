#pragma once
#include "../cpu.c"

#define _Z 0x80
#define _N 0x40
#define _H 0x20
#define _C 0x10

typedef unsigned char n;
typedef unsigned short nn;

typedef signed char r;

n checkBit(n *number, n bit) {
    return (*number >> bit) & 1U;
}

void setBit(n *number, n bit) {
    *number |= 1U << bit;
}

void resetBit(n *number, n bit) {
    *number &= ~(1U << bit);
}

n swapNibbles(n x) {
    return ( (x & 0x0F) << 4 | (x & 0xF0) >> 4 );
}

n rotateLeft(n x) {
    return (x << 1) | (x >> 7); 
}

n rotateRight(n x) {
    return (x >> 1) | (x << 7);
}