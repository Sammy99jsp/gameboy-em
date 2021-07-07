# gameboy-em

An attempt at making a Game Boy emulator in C — a language I have no experience in, lol — for the fxCG50 calculator.

## To Do List
| Feature | Status |
| ------- | ------ |
| CPU Structure | ✅ |
| RAM Structure | ✅ |
| Memory Mappers | ❓ |
| Video Stuff | ❓ |
| Instruction Set | ❓ |
| Search in Docs | ❓ |
| Adept for the fxCG50 | ❓ |
| Compile the thing | ❓ |

## Instruction Set
In the `docs` branch, I've quickly made a list of all the opcodes and their effect on flags.
You can look at it [here](https://sammy99jsp.github.io/gameboy-em/). 

## Types
To use roughly the same notation as the Game Boy CPU Manual<sup>[§1](#foot-1)</sup> and Instruction Set Table<sup>[§2](#foot-2)</sup>, I've defined the types below

```c
typedef unsigned char n;
typedef unsigned short nn;
typedef signed char r;
```

## CPU

In this implementation, the CPU is a struct of unions - which allows for registers to be accessed in pairs and directly all at once:
```c
union {
  nn BC;
  struct {
    n B;
    n C;
  }
}
```

The F register is implemented as a union to allow for flags to be directly accessed, and the entire F and AF registers.
```c
union {
  struct {
    unsigned char :4, C:1, H:1, N:1, Z;1;
  };
  n value;
}
```

## Resources
<a name="foot-1">§1</a>: [Game Boy CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf) — This is probably the best guide on GameBoy architecture.

<a name="foot-2">§2</a>: [GameBoy Instruction Set Table](https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html) — Used this as a source for the `docs` list.
