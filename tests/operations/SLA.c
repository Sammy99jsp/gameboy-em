#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/SLA.c"

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

    cpu.a   =   0b01101001;
    expected=   0b11010010;

    SLA(&cpu, &(cpu.a));

    tests[0] = (cpu.a == expected) && (cpu.f.C == 0);

    // Test 2

    cpu.b   =   0b10110011;
    expected=   0b01100110;

    SLA(&cpu, &(cpu.b));

    tests[1] = (cpu.b == expected) && (cpu.f.C == 1);
    
    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
