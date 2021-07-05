#include "./__includes__.c"

/**
 * @OPCODES 
 *  A0 → A, B
 *  A1 → A, C
 *  A2 → A, D
 *  A3 → A, E
 *  A4 → A, H
 *  A5 → A, L
 *  A6 → A, (HL)
 *  A7 → A, A
 * 
 *  E6 → A, n
*/

void AND(CPU *cpu, n *param1, n param2) {
    *param1 = (*param1) & param2;

    resetFlags(cpu, C + N);
    setFlags(cpu, H);
    if(*param1 == 0) {
        setFlags(cpu, Z);
    } else {
        resetFlags(cpu, Z);
    }
}
