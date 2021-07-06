#include "./__includes__.c"

/**
 * @MNEMONIC CCF
 * 
 * @FLAGS
 *  - 0 0 C
 * 
 * @OPCODES 
 *  3F
*/

void CCF(CPU *cpu) {
    cpu->f.C = !(cpu->f.C);

    cpu->f.N = 0;
    cpu->f.H = 0;
}
