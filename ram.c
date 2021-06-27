#include <stdio.h>

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

/* GameBoy RAM */

/* MEMORY MAP */
// 0x0000 - 0x3fff — ROM Bank 00                        16KB
// 0x4000 - 0x7fff — ROM Bank NN                        16KB
// 0x8000 - 0x9FFF — VRAM                               8KB
// 0xA000 - 0xBFFF — External RAM                       8KB
// 0xC000 - 0xCFFF — Work RAM 00                        8KB
// 0xD000 - 0xDFFF — Work Ram NN                        4KB
// 0xE000 - 0xFDFF — Mirror of 0xC000 - 0xDDFF          
// 0xFE00 - 0xFE9F — OAM
// 0xFEA0 - 0xFEFF — Not Usable
// 0xFF00 - 0xFF7F — IO Registers
// 0xFF80 - 0xFFFE — High RAM
// 0xFFFF - Interrupts Enable Register 

typedef struct {
    uint8_t ROM_BANK_00[0x4000];
    uint8_t ROM_BANK_NN[0x4000];
    uint8_t VRAM[0x2000];
    uint8_t EXT_RAM[0x2000];
    uint8_t WRAM_00[0x1000];
    uint8_t WRAM_NN[0x1000];
    uint8_t OAM[0x00A0];
    uint8_t IO[0x0080];
    uint8_t HRAM[0x007f];
    uint8_t IER[0x0001];
} Memory;

uint8_t read(Memory *MEM, uint16_t addr);
void write(Memory *MEM, uint16_t addr, uint8_t value);
uint8_t *ramAddress(Memory *MEM, uint16_t addr, int mode);

uint8_t *ramAddress(Memory *MEM, uint16_t addr, int mode) {
    if(addr < 0x4000) { return &(MEM->ROM_BANK_00[addr]); }
    if(addr < 0x8000) { return &(MEM->ROM_BANK_NN[addr - 0x4000]); }
    if(addr < 0xA000) { return &(MEM->VRAM[addr - 0x8000]); }
    if(addr < 0xC000) { return &(MEM->EXT_RAM[addr - 0xA000]); }
    if(addr < 0xD000) { return &(MEM->WRAM_00[addr - 0xC000]); }
    if(addr < 0xE000) { return &(MEM->WRAM_NN[addr - 0xD000]); }
    if(addr < 0xFE00) { 
        if(mode == 1) { return NULL; }
        return ramAddress(MEM, addr - 0x2000, mode); 
    }
    if(addr < 0xFEA0) { return &(MEM->OAM[addr - 0xFE00]); }
    if(addr < 0xFEFF) { return NULL; };
    if(addr < 0xFF80) { return &(MEM->IO[addr - 0xFF00]); }
    if(addr < 0xFFFF) { return &(MEM->HRAM[addr - 0xFF80]); }
    return &(MEM->IER[0]);
}

// Reading from Memory

uint8_t read(Memory *MEM, uint16_t addr) {
    return *(ramAddress(MEM, addr, 0));
}

void write(Memory *MEM, uint16_t addr, uint8_t value) {
    uint8_t *toChange = ramAddress(MEM, addr, 1);
    if(toChange == NULL) {
        return;
    }
    *toChange = value;
}


// Memory mappers
