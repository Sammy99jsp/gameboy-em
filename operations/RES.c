#include "./__includes__.c"

/**
 * @MNEMONIC RES
 * 
 * @FLAGS   :   - - - -
 * 
 * @OPCODES 
 * 
 *  CB 80 → $0, B
 *  CB 81 → $0, C
 *  CB 82 → $0, D
 *       ....
 *  CB 88 → $1, B
 *  CB 89 → $1, C
 *      ...
 *  CB 90 → $2, B
 *      ...
 *  CB BF → $7, A
 * 
 * Second arguement is actually the hex constant,
 * as it makes more sense for us to implement.
*/

void RES(CPU *cpu, n *param1, n param2) {
    // Do stuff...
    resetBit(param1, param2);
}
