#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/RL.c"

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

    // Test 1
    cpu.f.C =   0b1;    
    cpu.a =     0b01110100;

    n expected =0b11101001;

    RL(&cpu, &(cpu.a));

    tests[0] = (cpu.a == expected) && (cpu.f.C == 0);

    // Test 2

    cpu.f.C =   0b0;
    cpu.b   =   0b00110111;

    expected=   0b01101110;

    RL(&cpu, (&cpu.b));

    tests[1] = (cpu.b == expected) && (cpu.f.C == 0); 

    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
