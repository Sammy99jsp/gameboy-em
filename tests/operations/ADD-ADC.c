#include <stdio.h>
#include "../__includes__.c"
#include "../../cpu.c"
#include "../../operations/ADD-ADC.c"
/**
 * TESTS [❌,✔️,❓]
 *
 *  ❓ Test 1:
 *      Lorem Ipsum ?
 * 
*/

#define TESTS 11

int main() {
    CPU cpu;
    n expected;
    initCPU(&cpu);

    int tests[TESTS] = {0};

    // Test ADD here... 
    // tests[n] = (some boolean condition)... 
    
    // Test 1 — Simple, no carry, or halt carry
    cpu.a    = 0b00110110;
    cpu.b    = 0b11001001;
    expected = 0b11111111;

    ADD_n_n(&cpu, &(cpu.a), cpu.b);

    tests[0] = (cpu.a == expected)
        && (cpu.f.C == 0)
        && (cpu.f.H == 0)
        && (cpu.f.Z == 0)
        && (cpu.f.N == 0);

    // Test 2 — Normal carry, half carry, and zero.

    cpu.a    = 0b11111111;
    cpu.b    = 0b00000001;
    expected = 0b00000000;

    ADD_n_n(&cpu, &(cpu.a), cpu.b);

    tests[1] = (cpu.a == expected)
        && (cpu.f.C == 1)
        && (cpu.f.H == 1)
        && (cpu.f.N == 0)
        && (cpu.f.Z == 1);

    // Test 3 — Only half carry

    cpu.a    = 0b00001100;
    cpu.b    = 0b00000100;
    expected = 0b00010000;

    ADD_n_n(&cpu, &(cpu.a), cpu.b);

    tests[2] = (cpu.a == expected)
        && (cpu.f.C == 0)
        && (cpu.f.H == 1)
        && (cpu.f.N == 0)
        && (cpu.f.Z == 0);

    // Test 4 — Carry, and zero.

    cpu.a    = 0b11000000;
    cpu.b    = 0b01000000;
    expected = 0b00000000;

    ADD_n_n(&cpu, &(cpu.a), cpu.b);

    tests[3] = (cpu.a == expected)
        && (cpu.f.C == 1)
        && (cpu.f.H == 0)
        && (cpu.f.N == 0)
        && (cpu.f.Z == 1);

    // Test 5 — Carry only.

    cpu.a    = 0b11000000;
    cpu.b    = 0b01000001;
    expected = 0b00000001;

    ADD_n_n(&cpu, &(cpu.a), cpu.b);

    tests[4] = (cpu.a == expected)
        && (cpu.f.C == 1)
        && (cpu.f.H == 0)
        && (cpu.f.N == 0)
        && (cpu.f.Z == 0);
    

    // Test 6 — Zero only.

    cpu.a    = 0b00000000;
    cpu.b    = 0b00000000;
    expected = 0b00000000;

    ADD_n_n(&cpu, &(cpu.a), cpu.b);

    tests[5] = (cpu.a == expected)
        && (cpu.f.C == 0)
        && (cpu.f.H == 0)
        && (cpu.f.N == 0)
        && (cpu.f.Z == 1);
    
    // Test 7 — Two 16-bit numbers, with only half-carry (carry from bit 11)
    nn expected2;

    // HL        0110 1011 0010 1000
    // BC        0101 1000 1001 0000
    
    // expected  1100 0011 1011 1000
    cpu.hl   = 0b0110101100101000;
    cpu.bc   = 0b0101100010010000;
    expected2= 0b1100001110111000;

    ADD_nn_nn(&cpu, &(cpu.hl), cpu.bc);


    tests[6] = (cpu.hl == expected2)
        && (cpu.f.C == 0)
        && (cpu.f.H == 1)
        && (cpu.f.N == 0)
        && (cpu.f.Z == 0);


    // Test 8 — Carry, Half carry

    // HL           1011 1000 0000 0011
    // DE           0100 1000 0000 0001

    // expected     0000 0000 0000 0100

    cpu.hl =      0b1011100000000011;
    cpu.bc =      0b0100100000000001;

    expected2 =   0b0000000000000100;

    ADD_nn_nn(&cpu, &(cpu.hl), cpu.bc);

    tests[7] = (cpu.hl == expected2)
            && (cpu.f.C == 1)
            && (cpu.f.H == 1)
            && (cpu.f.Z == 0)
            && (cpu.f.N == 0);

    // Test 9 — Carry and Zero

    cpu.hl =      0b1111000000000000;
    cpu.de =      0b0001000000000000;

    expected2 =   0b0000000000000000;

    ADD_nn_nn(&cpu, &(cpu.hl), cpu.de);

    tests[8] = (cpu.hl == expected2)
            && (cpu.f.C == 1)
            && (cpu.f.H == 0)
            && (cpu.f.N == 0)
            && (cpu.f.Z == 1);


    // Test 10 — Only Zero

    cpu.hl =      0b0000000000000000;
    cpu.bc =      0b0000000000000000;

    expected2 =   0b0000000000000000;

    ADD_nn_nn(&cpu, &(cpu.hl), cpu.bc);

    tests[9] = (cpu.hl == expected2)
            && (cpu.f.C == 0)
            && (cpu.f.N == 0)
            && (cpu.f.H == 0)
            && (cpu.f.Z == 1);

    // Test 11 — Add nn, n

    cpu.sp =      0b1010000000000000;
    r r8   =     -24;

    expected2 = cpu.sp + r8; 

    ADD_nn_nn(&cpu, &(cpu.sp), r8);

    tests[10] = (cpu.sp == expected2)
            && (cpu.f.Z == 0)
            && (cpu.f.N == 0)
            && (cpu.f.C == 1)
            && (cpu.f.H == 0);

    /// /// /// /// ///
    
    // dumpCPU(&cpu);
    
    for (int i = 0; i < TESTS; i++) {
        if(tests[i]) {
            printf("Passed Test # %d !\n", i + 1);
        }
    }
}
