#include "./__includes__.c"

/**
 * @MNEMONIC RLC
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 00 → B
 *  CB 01 → C
 *  CB 02 → D
 *  CB 03 → E
 *  CB 04 → H
 *  CB 05 → L
 *  CB 06 → (HL)
 *  CB 07 → A
*/

void RLC(CPU *cpu, n *param1) {
    
    cpu->f.C = checkBit(param1, 7);

    *param1 = rotateLeft(*param1);

    cpu->f.Z = *param1 == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
}
