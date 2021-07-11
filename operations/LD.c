#include "./__includes__.c"

/**
 * @MNEMONIC LD
 * 
 * @FLAGS   :   - - - -
 * 
 * @OPCODES — Some should say LD and LDD are seperate,
 * but I call them the same operation.
 * 
 *  01 → BC, nn
 *  02 → (BC), A
 * ... literally fifty more...
*/

void LD_n_n(CPU *cpu, n *param1, n param2) {
    *param1 = param2;
}

void LD_nn_nn(CPU *cpu, nn *param1, nn param2) {
    *param1 = param2;
}