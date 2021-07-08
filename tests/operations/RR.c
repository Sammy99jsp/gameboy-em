#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/RR.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1
 *  ✔️ Test 2
 * 
*/

#define TESTS 2

int main() {
    n expected;
    CPU cpu;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test 1
    cpu.f.C =   0b1; 
    cpu.a   =   0b01011100;
    expected=   0b10101110;
    
    RR(&cpu, &(cpu.a));

    tests[0] = (cpu.a == expected) && (cpu.f.C == 0);
    
    // Test 2
    cpu.f.C =   0b1; 
    cpu.a   =   0b01110100;
    expected=   0b10111010;
    
    RR(&cpu, &(cpu.a));

    tests[1] = (cpu.a == expected) && (cpu.f.C == 0);

    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
