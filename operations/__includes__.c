#pragma once
#include "../cpu.c"

typedef unsigned char n;
typedef unsigned short nn;

typedef unsigned short flags;

typedef signed char r;

#define Z 0x80
#define N 0x40
#define H 0x20
#define C 0x10

// Bitwise stuff.

int testBit(n bits, n test);
n setBit(n bits, n toSet);
n resetBit(n bits, n toReset);
n toggleBit(n bits, n toToggle);
void setFlags(CPU *cpu, n toSet);
void resetFlags(CPU *cpu, n toSet);
void toggleFlags(CPU *cpu, n toSet);


int testBit(n bits, n test) {
    return (bits & test) == test;
}

n setBit(n bits, n toSet) {
    return bits | toSet; 
}

n resetBit(n bits, n toReset) {
    return bits & (~toReset);
}

n toggleBit(n bits, n toToggle) {
    return bits ^ toToggle;
}

void setFlags(CPU *cpu, n toSet) {
    cpu->f |= toSet;
}

void resetFlags(CPU *cpu, n toSet) {
    cpu->f &= ~toSet;
}

void toggleFlags(CPU *cpu, n toSet) {
    cpu->f ^= toSet;
}


