#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/OR.c"

/**
 * TESTS [❌,✔️,❓]
 * 
 *  ✔️ Test 1:
 *      Does param1 get updated with the correct value (the OR of *param1 and param2) ?
 *  
 *  ✔️ Test 2:
 *      Do the flags get updated accordingly (Z 0 0 0) ?
 * 
 * 
*/


int main() {
    CPU cpu;
    initCPU(&cpu);

    cpu.a = 0b00110100;
    cpu.b = 0b11001000;

    n result = cpu.a | cpu.b;

    OR(&cpu, &(cpu.a), cpu.b);
    dumpCPU(&cpu);

    int tests[2] = {0, 0};

    tests[0] = result == cpu.a;
    tests[1] = cpu.f.value == ((result == 0) << 7);


    for (int i = 0; i < 2; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}

