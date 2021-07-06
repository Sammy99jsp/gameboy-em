#include "./__includes__.c"

/**
 * @MNEMONIC SCF
 * 
 * @FLAGS   :   - 0 0 1
 * 
 * @OPCODES 
 * 
 *  37
*/

void SCF(CPU *cpu) {
    cpu->f.C = 1;
    
    cpu->f.N = 0;
    cpu->f.H = 0;
}
