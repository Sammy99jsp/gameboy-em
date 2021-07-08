#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/BIT.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1:
 *      (0, A) 
 *         → Z = 1
 * 
 *  ✔️  Test 2:
 *      (2, B)
 *         → Z = 0
 * 
 *  ✔️  Test 3:
 *      (5, H)
 *         → Z = 1
 * 
*/

#define TESTS 3

int main() {
    CPU cpu;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test 1

    n expected = 1;
    cpu.a = 0xFE;

    BIT(&cpu, &(cpu.a), 0); 
    
    tests[0] = expected == cpu.f.Z;

    // Test 2

    expected = 0;
    cpu.b = 0b10101100;

    BIT(&cpu, &(cpu.b), 2);

    tests[1] = expected == cpu.f.Z;

    // Test 3

    expected = 1;
    cpu.h = 0b11010110;

    BIT(&cpu, &(cpu.h), 5);

    tests[2] = expected == cpu.f.Z;

    /// /// /// /// ///

    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
