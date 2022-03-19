// Copyright 2022 Ayush Sharma

#pragma once

#define MAXMEM 65536 // 2^16

// Opcodes
#define NOP 0x0 // No operation
#define NXT 0x1 // Next
#define PRV 0x2 // Previous
#define INC 0x3 // Increment
#define DEC 0x4 // Decrement
#define JEZ 0x5 // Jump if zero flag is set
#define JNZ 0x6 // Jump if zero flag is not set
#define DSP 0x7 // Print current cell
#define LDS 0x8 // Take input at current cell
#define CPZ 0x9 // Sets zero-flag if current cell is 0
#define HLT 0xA // Halt
#define JMP 0xB // Jump to specified address
#define JMM 0xC // Change memory counter register to specified location
#define HCF 0xF // Halt and catch fire

int microvm(unsigned short* program, int program_length,char debug_flag);
char* getopcode(unsigned short op);