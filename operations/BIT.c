#include "./__includes__.c"

/**
 * @MNEMONIC BIT
 * 
 * @FLAGS   :   Z 0 1 -
 * 
 * @OPCODES 
 * 
 *  CB 40 → 0, B
 *  CB 41 → 0, C
 *  CB 41 → 0, D
 *      ....
 *  CB 47 → 0, A
 * 
 *  CB 48 → 1, B
 *      ....
 *  CB 4F → 1, A
 * 
 *  CB 50 → 2, B
 *      ....
 *  CB 57 → 2, A
 *      ....
 * 
 * @NOTE
 * 
 *      coded = (OPCODE - 0xCB40)
 *      
 *      Register Affected = coded % 8
 *      Bit to check      = coded / 8
*/

void BIT(CPU *cpu, n *param1, n param2) {
    
    cpu->f.Z = !checkBit(param1, param2);

    cpu->f.N = 0;
    cpu->f.H = 1;
}
