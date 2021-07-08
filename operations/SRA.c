#include "./__includes__.c"

/**
 * @MNEMONIC SRA
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 28 → B
 *  CB 29 → C
 *  CB 2A → D
 *  CB 2B → E
 *  CB 2C → H
 *  CB 2D → L
 *  CB 2E → (HL)
 *  CB 2F → A
 *  
*/

void SRA(CPU *cpu, n *param1) {
    // Shift the 0th bit into the carry.
    cpu->f.C = ((*param1) << 7) >> 7;

    // Do the right arithmetic shift part.
    *param1 = (((*param1) >> 7) << 7) | (*param1 >> 1);

    // Update the flags
    cpu->f.Z = (*param1) == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
}
