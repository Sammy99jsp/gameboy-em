#include "./__includes__.c"

/**
 * @MNEMONIC CPL
 * 
 * @FLAGS   :   - 1 1 -
 * 
 * @OPCODES 
 * 
 *  2F → A
*/

void CPL(CPU *cpu, n *param1) {
    *param1 = ~(*param1);
    cpu->f.N = 1;
    cpu->f.H = 1;
}
