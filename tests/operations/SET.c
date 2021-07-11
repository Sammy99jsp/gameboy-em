#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/SET.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ❓ Test 1
 *  ❓ Test 2
 * 
*/

#define TESTS 2

int main() {
    CPU cpu;
    n expected;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test SET here... 
    // tests[n] = (some boolean condition)... 
    
    // Test 1 — Set the 7th bit

    cpu.a    = 0b01011000;
    expected = 0b11011000;

    SET(&cpu, &(cpu.a), 7);

    tests[0] = cpu.a == expected;

    // Test 2 — Set a bit that is already set

    cpu.b    = 0b10110001;
    expected = 0b10110001;

    SET(&cpu, &(cpu.b), 0);

    tests[1] = cpu.b == expected;
    
    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
