#include "./__includes__.c"

/**
 * @MNEMONIC RR
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 18 → B
 *  CB 19 → C
 *  CB 1A → D
 *  CB 1B → E
 *  CB 1C → H
 *  CB 1D → L
 *  CB 1E → (HL)
 *  CB 1F → A
*/

void RR(CPU *cpu, n *param1) {
    n tmp = cpu->f.C; // Old value of C
    
    // Put 0th bit in the carry
    /// have to do this other shift thing as C only accepts 0 ... 1
    cpu->f.C = ((*param1) << 7) >> 7;
    
    *param1 = ((*param1) >> 1) | (tmp << 7);

    cpu->f.Z = (*param1) == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
}
