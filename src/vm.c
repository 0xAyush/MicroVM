// Copyright 2022 Ayush Sharma

// This file contains the code for the VM

#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "state.h"

int microvm(unsigned short* program,int program_length,char debug_flag) {
	unsigned short* memory = (unsigned short*)malloc(sizeof(unsigned short) * MAXMEM); // VM memory

	if(memory == NULL) {
		perror("Unable to allocate memory for VM");
		return 2;
	}

	for(int i = 0; i < MAXMEM - 1; i++) *(memory + i) = NOP;
	*(memory + MAXMEM - 1) = HCF;

	for(int i = 0; i < program_length; i++) { // Load the program
		*(memory + i) = *(program + i);
	}

	//Registers
	unsigned short memory_counter = 0;
	unsigned short program_counter = 0;
	unsigned short instruction_register[] = {0,0};

	//Flags
	unsigned short zero_flag = 0;
	unsigned short halt_flag = 0;
	unsigned short err_flag = 0;
	unsigned short jmp_flag = 0;
	unsigned short term_flag = 0;
	
	//Fetch, Decode, Execute Cycle
	while(!halt_flag && !term_flag) {
		jmp_flag = 0;
		//Fetch
		instruction_register[0] = *(memory + program_counter);
		instruction_register[1] = *(memory + program_counter + 1);

		if(debug_flag) {
			printf("INSTRUCTION : %s ",getopcode(instruction_register[0])); // Debugging helpers
			printf("PROGRAM COUNTER: %d ",program_counter);
			printf("MEMORY COUNTER: %d ",memory_counter);
			printf("DATA AT MEMORY: %d\n",memory[memory_counter]);
		}

				//Decode
		switch(instruction_register[0]) {
			//Execute
			case NXT: // Next op mem_counter++
			if(memory_counter < MAXMEM - 1) {
				memory_counter++;
			} else {
				memory_counter = 0;
			}
			break;

			case PRV: // Previous op mem_counter--
			if(memory_counter > 0) {
				memory_counter--;
			} else {
				memory_counter = MAXMEM - 1;
			}
			break;

			case INC: // Increment op
			*(memory + memory_counter) += 1;
			break;

			case DEC: // Decrement op
			*(memory + memory_counter) -= 1;
			break;
			
			case JEZ: // Jump if zero
			if(zero_flag) {
				program_counter = instruction_register[1];
				jmp_flag = 1;
			} else {
				program_counter += 1;
			}
			break;

			case JNZ: // Jump if not zero
			if(!zero_flag) {
				program_counter = instruction_register[1];
				jmp_flag = 1;
			} else {
				program_counter += 1;
			}
			break;

			case DSP: // Display
			unsigned short a = *(memory + memory_counter);
			printf("%x\n",a);
			break;

			case LDS: // Load
			char b[5];
			printf("? ");
			fgets(b,5,stdin);
			if(b[0] == 'q') {
				term_flag = 1;
				break;
			}
			unsigned short x = (unsigned short)atoi(b);
			*(memory + memory_counter) = x;
			break;

			case CPZ: // Is zero ?
			if(!*(memory + memory_counter)) {
				zero_flag = 1;
			} else {
				zero_flag = 0;
			}
			break;

			case HLT: // HALT
			halt_flag = 1;
			break;

			case JMP: // Jump
			program_counter = instruction_register[1];
			jmp_flag = 1;
			break;

			case JMM: // Take mem pointer to
			memory_counter = instruction_register[1];
			program_counter += 1;
			break;

			case NOP:
			break;

			default:
			printf("The VM halted and caught fire.\n");
			err_flag = 1;
			halt_flag = 1;
		}
		//Cycle, if there has been a jump leave the program counter alone (because if jmp to x but we change x it is silly)
		if(program_counter < MAXMEM - 1 && !jmp_flag) {
			program_counter += 1;
		} else if(!jmp_flag) {
			program_counter = 0;
		}
	}
	if(!err_flag && !term_flag) {
		printf("The program halted succesfully.\n");
	} else if(term_flag) {
		printf("Program terminated succesfully.\n");
	}
	return err_flag;
}

// For debug mode, get mneumonic from op
char* getopcode(unsigned short op) {
	char buf[8];
	if(op == NXT) return "NXT";
	else if(op == PRV) return "PRV";
	else if(op == INC) return "INC";
	else if(op == DEC) return "DEC";
	else if(op == JEZ) return "JEZ";
	else if(op == JNZ) return "JNZ";
	else if(op == DSP) return "DSP";
	else if(op == LDS) return "LDS";
	else if(op == CPZ) return "CPZ";
	else if(op == HLT) return "HLT";
	else if(op == JMP) return "JMP";
	else if(op == JMM) return "JMM";
	else if(op == NOP) return "NOP";
	else if(op == HCF) return "HCF";
	else return itoa((int) op,buf,10);
}