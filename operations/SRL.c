#include "./__includes__.c"

/**
 * @MNEMONIC SRL
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 38 → B
 *  CB 39 → C
 *  CB 3A → D
 *  CB 3B → E
 *  CB 3C → H
 *  CB 3D → L
 *  CB 3E → (HL)
 *  CB 3F → A
 
*/

void SRL(CPU *cpu, n *param1) {
    
    *param1 = (*param1) >> 1;

    cpu->f.Z = (*param1) == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
    cpu->f.C = (*param1 >> 0) & 1;

}
