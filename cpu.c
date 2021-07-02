#include <stdio.h>
#include "./ram.c"

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define TRUE 1
#define FALSE 0

#define FLAG_Z 0x80
#define FLAG_S 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

typedef struct {
    union {
        uint16_t af;
        struct {
            uint8_t a;
            uint8_t f;
        };
    };
    union {
        uint16_t bc;
        struct {
            uint8_t b;
            uint8_t c;
        };
    };
    union {
        uint16_t de;
        struct {
            uint8_t d;
            uint8_t e;
        };
    };
    union {
        uint16_t hl;
        struct {
            uint8_t h;
            uint8_t l;
        };
    };

    uint16_t sp;
    uint16_t pc;
} CPU;

CPU cpu;
Memory memory;

uint8_t *_hl_();
uint8_t *_hl_() {
    return ramAddress(&memory, cpu.hl, 0);
}

void executeCode(uint8_t code);

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
int hasFlag(int flag, CPU *CPU);


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

void executeCode(uint8_t code) {
    if(code == 0x36) {

    }
    if(code > 0x39 && code < 0x80) {
        uint8_t *regs[8] = {&(cpu.b), &(cpu.c), &(cpu.d), &(cpu.e), &(cpu.h), &(cpu.l), _hl_(), &(cpu.a)};
        uint8_t *targetRegister = regs[(code - 0x40) / 0x08];
        uint8_t *sourceRegister = regs[(code - 0x40) % 0x08]; 
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
    executeCode(0x5A);
    dumpCPU();
}