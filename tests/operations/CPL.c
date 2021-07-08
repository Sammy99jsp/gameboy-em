#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/CPL.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1:
 *          Check if complement is set .
 *  
 *  ✔️  Test 2:
 *          Check if flags are set.
 * 
*/

#define TESTS 2

int main() {
    CPU cpu;
    initCPU(&cpu);

    int tests[TESTS] = {0};



    // Test 1 — Check if the complement is set;
    cpu.a =  0b11001000;
    n test = 0b00110111;
    
    
    CPL(&cpu, &(cpu.a));

    printf("A: \t\t\t"BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(cpu.a));
    printf("expected:\t"BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(test));

    tests[0] = (cpu.a == test);

    // Test 2 — Check if flags are changed accordingly.

    // Flags Before - Z 0 H C
    cpu.f.value = 0b10110000;

    CPL(&cpu, &(cpu.a));
    tests[1] = cpu.f.value == 0b11110000; 

    // dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        } else {
            printf("Failed Test # %d !\n", i + 1);
        }
    }
}
