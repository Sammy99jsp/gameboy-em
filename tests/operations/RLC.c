#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/RLC.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1
 * 
 *  ✔️ Test 2
 * 
*/

#define TESTS 3

int main() {
    CPU cpu;
    initCPU(&cpu);

    n expected;

    int tests[TESTS] = {0};


    // Test 1 — Check if the rotation is correct

    cpu.a =     0b10110110;
    expected =  0b01101101;

    RLC(&cpu, &(cpu.a));

    tests[0] = cpu.a == expected;

    // Test 2 — Check Carry Flag

    tests[1] = cpu.f.C == 1;

    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
