#include "./__includes__.c"

/**
 * @MNEMONIC RRC
 * 
 * @FLAGS   :   Z 0 0 C
 * 
 * @OPCODES 
 * 
 *  CB 08 → B
 *  CB 09 → C
 *  CB 0A → D
 *  CB 0B → E
 *  CB 0C → H
 *  CB 0D → L
 *  CB 0E → (HL)
 *  CB 0F → A
 *  0F    → A
*/

void RRC(CPU *cpu, n *param1) {
    cpu->f.C = checkBit(param1, 0);

    *param1 = rotateRight(*param1);

    cpu->f.Z = *param1 == 0;
    cpu->f.N = 0;
    cpu->f.H = 0;
}
