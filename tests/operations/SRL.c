#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/SRL.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1:
 * 
*/

#define TESTS 2

int main() {
    n expected;
    CPU cpu;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test 1

    cpu.a   =   0b01010011;
    expected=   0b00101001;

    SRL(&cpu, &(cpu.a));

    tests[0] = (cpu.a == expected) && (cpu.f.C == 1);

    // Test 2

    cpu.b   =   0b00100010;
    expected=   0b00010001;

    SRL(&cpu, &(cpu.b));

    tests[1] = (cpu.b == expected) && (cpu.f.C == 0);
    /// /// /// /// ///
    
    // dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
