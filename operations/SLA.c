#include "./__includes__.c"

/**
 * @MNEMONIC SLA
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 20 → B
 *  CB 21 → C
 *  CB 22 → D
 *  CB 23 → E
 *  CB 24 → H
 *  CB 25 → L
 *  CB 26 → (HL)
 *  CB 27 → A
 *  
*/

void SLA(CPU *cpu, n *param1) {
    
    // Put HSB into carry.
    cpu->f.C = (*param1) >> 7; 

    // Shift the entire thing left.
    *param1 = (*param1) << 1;
    
    // Update flags.
    cpu->f.Z = (*param1) == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
}
