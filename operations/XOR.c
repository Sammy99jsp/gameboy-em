#include "./__includes__.c"

/**
 * @MNEMONIC XOR 
 * 
 * @FLAGS
 *  Z 0 0 0
 * 
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
    
    cpu->f.C = 0;
    cpu->f.H = 0;
    cpu->f.N = 0;
    cpu->f.Z = *param1 == 0;
}
