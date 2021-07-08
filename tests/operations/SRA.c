#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/SRA.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ❓ Test 1
 * 
*/

#define TESTS 2

int main() {
    n expected;
    CPU cpu;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test 1
    cpu.a   =   0b11010001;
    expected=   0b11101000;

    SRA(&cpu, &(cpu.a));

    tests[0] = (cpu.a == expected) && (cpu.f.C == 1);

    // Test 2

    cpu.b   =   0b01001101;
    expected=   0b00100110;

    SRA(&cpu, &(cpu.b));

    tests[1] = (cpu.b == expected) && (cpu.f.C == 1);

    /// /// /// /// ///
    
    // dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
