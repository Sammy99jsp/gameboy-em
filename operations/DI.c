#include "./__includes__.c"

/**
 * @MNEMONIC DI
 * 
 * @FLAGS   :   - - - -
 * 
 * @OPCODES 
 * 
 *  F3
*/

void DI(CPU *cpu) {
    cpu->hasInterupts = 0;    
}
