// Copright 2022 Ayush Sharma

#pragma once

#define MAXMEM 65536 // 2^16

// Opcodes
#define NXT 0x0 // Next
#define PRV 0x1 // Previous
#define INC 0x2 // Increment
#define DEC 0x3 // Decrement
#define JEZ 0x4 // Jump if zero flag is set
#define JNZ 0x5 // Jump if zero flag is not set
#define DSP 0x6 // Print current cell
#define LDS 0x7 // Take input at current cell
#define CPZ 0x8 // Sets zero-flag if current cell is 0
#define HLT 0x9 // Halt
#define JMP 0xA // Jump to specified address
#define JMM 0xB // Change memory counter register to specified location
#define NOP 0xC // No operation
#define HCF 0XFF // Halt and catch fire

int microvm(unsigned short* program, int program_length);