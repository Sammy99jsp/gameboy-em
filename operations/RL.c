#include "./__includes__.c"

/**
 * @MNEMONIC RL
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 10 → B
 *  CB 11 → C
 *  CB 12 → D
 *  CB 13 → E
 *  CB 14 → H
 *  CB 15 → L
 *  CB 16 → (HL)
 *  CB 17 → A
*/

void RL(CPU *cpu, n *param1) {
    // Manually done — No helper function here! 

    n tmp = cpu->f.C; // Old value of C
    
    cpu->f.C = (*param1) >> 7; // Put 7th bit in the carry
    *param1 = ((*param1) << 1) | tmp;

    cpu->f.Z = (*param1) == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
}
