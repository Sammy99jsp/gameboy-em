#include "./__includes__.c"

/**
 * @MNEMONIC EI
 * 
 * @FLAGS   :   - - - -
 * 
 * @OPCODES 
 * 
 *  BF
*/

void EI(CPU *cpu) {
    cpu->hasInterupts = 1;    
}
