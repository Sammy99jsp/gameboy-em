#include "./__includes__.c"

/**
 * @MNEMONIC SWAP
 * 
 * @FLAGS   :   Z 0 0 0
 * 
 * @OPCODES 
 * 
 *  CB 30 → B
 *  CB 31 → C
 *  CB 32 → D
 *  CB 33 → E
 *  CB 34 → H
 *  CB 35 → L
 *  CB 36 → (HL)
 *  CB 37 → A
*/

void SWAP(CPU *cpu, n *param1) {
    
    *param1 = swapNibbles(*param1);

    cpu->f.Z = (*param1) == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
    cpu->f.C = 0;
}
