#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/XOR.c"

/**
 * TESTS
 *  ✅ Test 1:
 *      Does param1 get updated with the correct value (the XOR of *param1 and param2) ?
 *  
 *  ✅ Test 2:
 *      Do the flags get updated accordingly (Z 0 0 0) ?
 * 
*/


int main() {
    CPU cpu;
    initCPU(&cpu);

    cpu.a = 0b11001010;
    cpu.b = 0b11001010;

    n result = cpu.a ^ cpu.b;

    XOR(&cpu, &(cpu.a), cpu.b);
    dumpCPU(&cpu);

    int tests[2] = {0, 0};

    tests[0] = result == cpu.a;
    tests[1] = cpu.f == ((result == 0) << 7);


    for (int i = 0; i < 2; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}

