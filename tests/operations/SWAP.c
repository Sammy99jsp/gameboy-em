#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/SWAP.c"

/**
 * TESTS [❌,✔️,❓]
 *
 *  ✔️ Test 1
 * 
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

    cpu.a =     0b10010011;
    expected =  0b00111001;

    SWAP(&cpu, &(cpu.a));

    tests[0] = cpu.a == expected;

    // Test 2

    cpu.b =     0b11101010;
    expected =  0b10101110;

    SWAP(&cpu, &(cpu.b));

    tests[1] = cpu.b == expected;

    /// /// /// /// ///
    
    dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
