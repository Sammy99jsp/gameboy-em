#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/SCF.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ❓ Test 1:
 *      IN;         0 0 0 0
 *      EXPECTED;   0 0 0 1 
 * 
 *  ❓ Test 2:
 *      IN;         1 1 1 0
 *      EXPECTED;   1 0 0 1 
 * 
*/

#define TESTS 2

int main() {
    CPU cpu;
    initCPU(&cpu);

    int tests[TESTS];
    
    // Test 1

    cpu.f.value = 0b00000000;    
    n expected = 0b00010000;

    SCF(&cpu);
    tests[0] = cpu.f.value == expected;

    // Test 2

    cpu.f.value = 0b11100000;
    n expected2 = 0b10010000;

    SCF(&cpu);
    tests[1] = cpu.f.value == expected2;

    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
