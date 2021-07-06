#include "cpu.c"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

int main() {
    CPU cpu;

    initCPU(&cpu);

    cpu.f.value = 0b11010000;
    cpu.f.C = 0;
    cpu.f.Z = 0;
    printf("hello! "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(cpu.f.value));
    return 0;
}
