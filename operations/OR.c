#include "./__includes__.c"

/**
 * @MNEMONIC OR
 * 
 * @FLAGS
 *  Z 0 0 0  
 * 
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
    
    cpu->f.C = 0;
    cpu->f.H = 0;
    cpu->f.N = 0;
    cpu->f.Z = (*param1) == 0;
}
