#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/RRC.c"

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
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test 1 — Test the right rotatation's validity

    cpu.a =         0b01011101;
    n expected =    0b10101110;

    RRC(&cpu, &(cpu.a));

    tests[0] = cpu.a == expected;

    // Test 2 — Check the flags

    tests[1] = (cpu.f.C == 1) && (!cpu.f.Z); 

    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
