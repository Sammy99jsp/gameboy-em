#include "./__includes__.c"

/**
 * @OPCODES 
 *  B0 → A, B
 *  B1 → A, C
 *  B2 → A, D
 *  B3 → A, E
 *  B4 → A, H
 *  B5 → A, L
 *  B6 → A, (HL)
 *  B7 → A, A
 * 
 *  F6 → A, n
*/

void OR(CPU *cpu, n *param1, n param2) {
    *param1 = (*param1) | param2;

    resetFlags(cpu, C + H + N);
    
    if(*param1 == 0) {
        setFlags(cpu, (1<<7));
    } else {
        resetFlags(cpu, (1<<7));
    }
}
