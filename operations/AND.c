#include "./__includes__.c"

/**
 * @MNEMONIC AND
 * 
 * @FLAGS
 *  Z 0 1 0
 * 
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

    cpu->f.Z = *param1 == 0;
    cpu->f.N = 0;
    cpu->f.H = 1;
    cpu->f.C = 0;
}
