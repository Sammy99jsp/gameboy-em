#include "./cpu.c"

typedef unsigned char n;
typedef unsigned short nn;

typedef unsigned short flags;

typedef signed char r;

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

CPU cpu;

void NOP();

void LD_n_n(n *dest, n value);
void LD_nn_nn(nn *dest, nn value);

void INC_n(n *dest);
void INC_nn(nn *dest);

void DEC_n(n *dest);
void DEC_nn(nn *dest);


void JR_r(r value);
void JR_cond_r(flags cond, r value);

void ADD_n_n(n *dest, n value);
void ADD_nn_nn(nn *dest, nn value);
void ADD_nn_n(nn *dest, n value);
void ADC_n_n(n *dest, n value);

void SUB_n_n(n *dest, n value);
void SBC_n_n(n *dest, n value);

void AND_n_n(n *dest, n source);

void XOR_n_n(n *dest, n source);

void OR_n_n(n *dest, n source);

void CP_n(n *dest, n source);

void RET();
void RET(flags condition);
void RETI();

void POP_nn(nn *dest);

void CALL(nn *dest);
void CALL(flags condition, nn *dest);

void RST(n value);

void PUSH_nn(nn value);

void STOP();

void DI();
void EI();

void RLC_n(n *dest);
void RL_n(n *dest);

void RRC_n(n *dest);
void RR_n(n *dest);

void SLA(n *dest);

void SLR(n *dest);
void SRL(n *dest);

void SWAP(n *dest);

void BIT(n bit, n *dest);

void RES(n bit, n *dest);

void SET(n bit, n *dest);

// Bitwise stuff.

int testBit(n bits, n test);
n setBit(n bits, n toSet);
n resetBit(n bits, n toReset);
n toggleBit(n bits, n toToggle);


int testBit(n bits, n test) {
    return (bits & test) == test;
}

n setBit(n bits, n toSet) {
    return bits | toSet; 
}

n resetBit(n bits, n toReset) {
    return bits & (~toReset);
}

n toggleBit(n bits, n toToggle) {
    return bits ^ toToggle;
}

// Shortenings
void setZFlag();
void setNFlag();
void setHFlag();
void setCFlag();

void resetZFlag();
void resetNFlag();
void resetHFlag();
void resetCFlag();

int hasHalfCarry(n a, n b);

void setZFlag() {
    cpu.f = setBit(cpu.f, FLAG_Z);
}

void setNFlag() {
    cpu.f = setBit(cpu.f, FLAG_N);
}
void setHFlag() {
    cpu.f = setBit(cpu.f, FLAG_H);
}
void setCFlag() {
    cpu.f = setBit(cpu.f, FLAG_C);
}


void resetZFlag() {
    cpu.f = resetBit(cpu.f, FLAG_Z);
}

void resetNFlag() {
    cpu.f = resetBit(cpu.f, FLAG_N);
}
void resetHFlag() {
    cpu.f = resetBit(cpu.f, FLAG_H);
}
void resetCFlag() {
    cpu.f = resetBit(cpu.f, FLAG_C);
}

int hasHalfCarry(n a, n b) {
    return (((a & 0xf) + (b & 0xf)) & 0x10) == 0x10;
}

// Instruction definitions

void NOP() {
    return;
}

void LD_n_n(n *dest, n source) {
    *dest = source;
}

void LD_nn_nn(nn *dest, nn source) {
    *dest = source;
}

void INC_n(n *dest) {
    if(*dest + 1 == 0) {
        setZFlag();
    } else {
        resetZFlag();
    }

    if(hasHalfCarry(*dest, 1)) {
        setHFlag();
    } else {
        resetHFlag();
    }

    resetNFlag();

    *dest += 1;
}

void INC_nn(nn *dest) {
    *dest += 1;
}

void DEC_n(n *dest) {
    if(*dest - 1 == 0) {
        setZFlag();
    } else {
        resetZFlag();
    }

    if(hasHalfCarry(*dest, -1)) {
        setHFlag();
    } else {
        resetHFlag();
    }

    setNFlag();

    *dest -= 1;
}

void DEC_nn(nn *dest) {
    *dest -= 1;
}

void JR_r(r value) {
    cpu.pc += value;
}

void JR_cond_r(flags cond, r value) {
    if(testBit(cpu.f, cond)) {
        JR_r(value);
    }
}

void ADD_n_n(n *dest, n value) {
    if(*dest + value == 0) {
        setZFlag();
    } else {
        resetZFlag();
    }

    if(hasHalfCarry(*dest, value)) {
        setHFlag();
    } else {
        resetHFlag();
    }

    if((*dest + value ) > 0xFF) {
        setCFlag();
    } else {
        resetCFlag();
    }

    resetNFlag();

    *dest -= 1;
}