#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/RES.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1
 *  ✔️ Test 2
 * 
*/

#define TESTS 2

int main() {
    CPU cpu;
    n expected;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test RES here... 
    // tests[n] = (some boolean condition)... 
    
    // Test 1 — Reset the 4th bit.

    cpu.a   = 0b10110000;
    expected= 0b10100000;

    RES(&cpu, &(cpu.a), 4);

    tests[0] = cpu.a == expected;

    // Test 2 — Reset the 7th bit.

    cpu.b   = 0b10011001;
    expected= 0b00011001;

    RES(&cpu, &(cpu.b), 7);

    tests[1] = cpu.b == expected;

    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
