#include "./__includes__.c"

/**
 * @OPCODES 
 *  A8 → A, B
 *  A9 → A, C
 *  AA → A, D
 *  AB → A, E
 *  AC → A, H
 *  AD → A, L
 *  AE → A, (HL)
 *  AF → A, A
 * 
 *  EE → A, n
*/

void XOR(CPU *cpu, n *param1, n param2) {
    *param1 = (*param1) ^ param2;

    resetFlags(cpu, C + H + N);
    
    if(*param1 == 0) {
        setFlags(cpu, Z);
    } else {
        resetFlags(cpu, Z);
    }
}
