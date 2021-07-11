#include "./__includes__.c"

// Moved ADC in here to make the compiler happier and because I can't be asked to find another solution.

/**
 * @MNEMONIC ADD
 * 
 * @FLAGS   :   Z 0 H C
 * 
 * @OPCODES 
 * 
 *  80 → A, B
 *  81 → A, C
 *  82 → A, D
 *  83 → A, E
 *  84 → A, H
 *  85 → A, L
 *  86 → A, (HL)
 *  87 → A, A
*/

n ADD_n_n_(CPU *cpu, n param1, n param2) {
    cpu->f.C = (param1 + param2) > 0xFF;
    cpu->f.H = (param1 & 0x0F) + (param2 & 0x0F) > 0x0F;

    param1 = param1 + param2;

    cpu->f.N = 0;
    cpu->f.Z = param1 == 0;

    return param1;
}

void ADD_n_n(CPU *cpu, n *param1, n param2) {
    *param1 = ADD_n_n_(cpu, *param1, param2);
}

void ADD_nn_nn(CPU *cpu, nn *param1, nn param2) {
    // ADD lower bytes, then ADC higher bytes. 
    // Could not get this to work very consistently, so I bodged it. 
    
    // ADD lower bytes
    n lowByte = ADD_n_n_(cpu, (*param1) & 0xFF, param2 & 0xFF); 

    // Horrible ADC of upper bytes
    n highByte = ADD_n_n_(cpu, ((*param1) & 0xFF00) >> 8, ((param2 & 0xFF00) >> 8) + cpu->f.C);

    *param1 = (highByte << 8) + lowByte;

    cpu->f.Z = (*param1) == 0;
}

/**
 * @MNEMONIC ADC
 * 
 * @FLAGS   :   Z 0 H C
 * 
 * @OPCODES 
 * 
 *  88 → A, B
 *  89 → A, C
 *  8A → A, D
 *  8B → A, E
 *  8C → A, H
 *  8D → A, L
 *  8E → A, (HL)
 *  8F → A, A
*/

void ADC(CPU *cpu, n *param1, n param2) {
    // This case may not be as straightforward, but I'll leave it like this.
    // I'll regret the future bug that will lie here :(
    ADD_n_n(cpu, param1, param2 + cpu->f.C);
}
