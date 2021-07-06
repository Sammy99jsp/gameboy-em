#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/AND.c"

/**
 * 
 * TESTS [❌,✔️,❓]
 * 
 *   Test 1:
 *  ✔️ Does param1 get updated with the correct value (the AND of *param1 and param2) ?
 *  
 *  ✔️ Test 2:
 *      Do the flags get updated accordingly (Z 0 1 0) ?
 * 
*/

#define TESTS 2

int main() {
    CPU cpu;
    initCPU(&cpu);

    cpu.a = 0x34;
    cpu.b = 0x12;

    n result = cpu.a & cpu.b;

    AND(&cpu, &(cpu.a), cpu.b);
    dumpCPU(&cpu);

    int tests[TESTS] = {0, 0};

    tests[0] = result == cpu.a;
    tests[1] = cpu.f.value == ((result == 0) << 7) + _H;


    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}

