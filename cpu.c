#pragma once
#include "./ram.c"

typedef unsigned short nn;
typedef unsigned char n;

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

typedef struct {
    union {
        nn af;
        struct {
            n a;
            union {
                // The following works with my compiler, but your milage may vary ...
                struct {
                    unsigned char : 4, C:1, H:1, N:1, Z:1;
                };
                n value;
            } f;
        };
    };
    union {
        nn bc;
        struct {
            n b;
            n c;
        };
    };
    union {
        nn de;
        struct {
            n d;
            n e;
        };
    };
    union {
        nn hl;
        struct {
            n h;
            n l;
        };
    };

    nn sp;
    nn pc;
    // Are interrupts enabled?
    n hasInterupts : 1;
} CPU;

/*
    Flag byte is implmented as such: 

    Z S H C 0 0 0 0

    Z - Zero — if last operation resulted in a zero.
    S - Subtraction - If last operation was a subtraction.
    H - If last operation resulted in a nibble carry.
    C - If last operation resulted in a carry.
*/

void initCPU(CPU *CPU);
void dumpCPU();


void initCPU(CPU *cpu) {
    cpu->af = 0x0000;
    cpu->bc = 0x0000;
    cpu->de = 0x0000;
    cpu->hl = 0x0000;
    cpu->sp = 0x0000;
    cpu->pc = 0x0000;
}

void dumpCPU(CPU *cpu) {
    printf("--- CPU ---\n");
    printf("\t A -> 0x%02hhX\n", cpu->a);
    printf("\t B -> 0x%02hhX\n", cpu->b);
    printf("\t C -> 0x%02hhX\n", cpu->c);
    printf("\t D -> 0x%02hhX\n", cpu->d);
    printf("\t E -> 0x%02hhX\n", cpu->e);
    printf("\t F -> 0x%02hhX\n", cpu->f);
    printf("\t H -> 0x%02hhX\n", cpu->h);
    printf("\t L -> 0x%02hhX\n", cpu->l);
    printf("\n");
}