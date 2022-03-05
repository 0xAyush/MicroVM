#include <stdio.h>
#include <stdlib.h>

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

//Program
//TODO: Load state from file.
#define PROGRAM_LENGTH 10
unsigned short program[PROGRAM_LENGTH] = {HLT,0,0,0,0,0,0,0,0,0};

int main() {
	unsigned short* memory = malloc(sizeof(unsigned short) * MAXMEM);
	for(int i = 0; i < MAXMEM; i++) *(memory + i) = 0;
	//Registers
	unsigned short memory_counter = 0;
	unsigned short program_counter = 0;
	unsigned short instruction_register[] = {0,0};
	//Flags
	unsigned short zero_flag = 0;
	unsigned short halt_flag = 0;
	unsigned short err_flag = 0;
	unsigned short jmp_flag = 0;

	for(int i = 0; i < PROGRAM_LENGTH; i++) {
		*(memory + i) = program[i];
	}
	
	//Fetch, Decode, Execute Cycle
	while(!halt_flag) {
		jmp_flag = 0;
		//Fetch
		instruction_register[0] = *(memory + program_counter);
		instruction_register[1] = *(memory + program_counter + 1);
		//Decode
		switch(instruction_register[0]) {
			//Execute
			case NXT:
			if(memory_counter < MAXMEM - 1) {
				memory_counter++;
			} else {
				memory_counter = 0;
			}
			break;

			case PRV:
			if(memory_counter > 0) {
				memory_counter--;
			} else {
				memory_counter = MAXMEM - 1;
			}
			break;

			case INC:
			*(memory + memory_counter) += 1;
			break;

			case DEC:
			*(memory + memory_counter) -= 1;
			break;
			
			case JEZ:
			if(zero_flag) {
				program_counter = instruction_register[1];
				jmp_flag = 1;
			}
			break;

			case JNZ:
			if(!zero_flag) {
				program_counter = instruction_register[1];
				jmp_flag = 1;
			}
			break;

			case DSP:
			unsigned short a = *(memory + memory_counter);
			printf("%x\n",a);
			break;

			case LDS:
			unsigned short b = 0;
			printf("? ");
			scanf(" %d",&a);
			break;

			case CPZ:
			if(!*(memory + memory_counter)) {
				zero_flag = 1;
			} else {
				zero_flag = 0;
			}
			break;

			case HLT:
			halt_flag = 1;
			break;

			case JMP:
			program_counter = instruction_register[1];
			jmp_flag = 1;
			break;

			case JMM:
			memory_counter = instruction_register[1];
			program_counter += 1;
			break;

			default:
			printf("The VM halted and caught fire.");
			err_flag = 1;
			halt_flag = 1;
		}
		//Cycle
		if(program_counter < MAXMEM - 1 && !jmp_flag) {
			program_counter += 1;
		} else if(!jmp_flag) {
			program_counter = 0;
		}
	}
	if(!err_flag) {
		printf("The program halted succesfully.\n");
	}
	return 0;
}