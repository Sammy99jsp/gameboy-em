#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/CCF.c"

/**
 * TESTS [❌,✔️,❓]
 *  
 *   Test 1:
 *     ✔️ Do the flags get updated accordingly (Z 0 1 0) ?
 * 
*/


int main() {
    CPU cpu;
    initCPU(&cpu);

   
    dumpCPU(&cpu);

    int tests[3] = {0, 0, 0};

    CCF(&cpu);

    tests[0] = cpu.f.value == _C;

    CCF(&cpu);

    tests[1] = cpu.f.value == 0;

    cpu.f.value = _Z + _N + _H + _C;

    CCF(&cpu);

    // Z unaffected, 1; N is 0; H is 0; C flag toggled, 0

    tests[2] = cpu.f.value == _Z;

    for (int i = 0; i < 3; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}

