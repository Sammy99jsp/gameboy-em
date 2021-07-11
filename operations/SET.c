#include "./__includes__.c"

/**
 * @MNEMONIC SET
 * 
 * @FLAGS   :   - - - -
 * 
 * @OPCODES 
 * 
 *  CB C0 → $0, B
 *  CB C1 → $0, C
 *  CB C2 → $0, D
 *      ....
 *  CB C8 → $1, B
 *  CB C9 → $1, C
 *      ....
 *  CB FF → $7, A
 * 
 *  See notes for res.
*/

void SET(CPU *cpu, n *param1, n param2) {
    setBit(param1, param2);
}
