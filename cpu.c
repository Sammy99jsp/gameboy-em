#include <stdio.h>
#include "./ram.c"
#include "./opcodes.c"

typedef unsigned short nn;
typedef unsigned char n;


#define TRUE 1
#define FALSE 0

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

struct CPU {
    union {
        nn af;
        struct {
            n a;
            n f;
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
};

typedef struct CPU CPU;
extern Memory memory;
extern CPU cpu;


n *_hl_();
n *_hl_() {
    return ramAddress(&memory, cpu.hl, 0);
}

void executeCode(n code);

// Flag byte is implmented as such: 
/*
    Z S H C 0 0 0 0

    Z - Zero — if last operation resulted in a zero.
    S - Subtraction - If last operation was a subtraction.
    H - If last operation resulted in a nibble carry.
    C - If last operation resulted in a carry.
*/

void initCPU(CPU *CPU);
void dumpCPU();


void initCPU(CPU *CPU) {
    CPU->af = 0x0000;
    CPU->bc = 0x0000;
    CPU->de = 0x0000;
    CPU->hl = 0x0000;
    CPU->sp = 0x0000;
    CPU->pc = 0x0000;
}

void dumpCPU() {
    printf("--- CPU ---\n");
    printf("\t A -> 0x%02hhX\n", cpu.a);
    printf("\t B -> 0x%02hhX\n", cpu.b);
    printf("\t C -> 0x%02hhX\n", cpu.c);
    printf("\t D -> 0x%02hhX\n", cpu.d);
    printf("\t E -> 0x%02hhX\n", cpu.e);
    printf("\t F -> 0x%02hhX\n", cpu.f);
    printf("\t H -> 0x%02hhX\n", cpu.h);
    printf("\t L -> 0x%02hhX\n", cpu.l);
    printf("\n");
}


// void LD_NN_N(uint8_t *reg1, uint8_t *reg2);

// // LD nn, n
// void LD_NN_N(uint8_t *reg1, uint8_t val) {
//     *reg1 = val;
// }

void executeCode(n code) {
    if(code == 0x36) {

    }
    if(code > 0x39 && code < 0x80) {
        n *regs[8] = {&(cpu.b), &(cpu.c), &(cpu.d), &(cpu.e), &(cpu.h), &(cpu.l), _hl_(), &(cpu.a)};
        n *targetRegister = regs[(code - 0x40) / 0x08];
        n *sourceRegister = regs[(code - 0x40) % 0x08]; 
        printf("Target, %d\n", (code - 0x40) / 0x08);
        printf("Target Val, %d\n", *targetRegister);
        printf("Source, %d\n", (code - 0x40) % 0x08);
        printf("Source Val, %d\n\n", *sourceRegister);
        *targetRegister = *sourceRegister;
    }
}


int main () {
    initCPU(&cpu);
    write(&memory, 0xC000, 0x70);
    cpu.d = 0xC1;
    dumpCPU();
    //executeCode(0x5A);
    ADD_n_n(&(cpu.d), 0x03);
    dumpCPU();
}