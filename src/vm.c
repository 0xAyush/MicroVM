// Copright 2022 Ayush Sharma

#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "state.h"

int microvm(unsigned short* program,int program_length) {
	unsigned short* memory = (unsigned short*)malloc(sizeof(unsigned short) * MAXMEM);

	if(memory == NULL) {
		perror("Unable to allocate memory for VM");
		return 2;
	}

	for(int i = 0; i < MAXMEM - 1; i++) *(memory + i) = NOP;
	*(memory + MAXMEM - 1) = HCF;
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

	for(int i = 0; i < program_length; i++) {
		*(memory + i) = *(program + i);
	}
	
	//Fetch, Decode, Execute Cycle
	while(!halt_flag && !term_flag) {
		jmp_flag = 0;
		//Fetch
		instruction_register[0] = *(memory + program_counter);
		instruction_register[1] = *(memory + program_counter + 1);
		/*printf("INSTRUCTION : %d ",instruction_register[0]); // Debugging helpers
		printf("PROGRAM COUNTER: %d ",program_counter);
		printf("MEMORY COUNTER: %d\n",memory_counter);*/
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
			} else {
				program_counter += 1;
			}
			break;

			case JNZ:
			if(!zero_flag) {
				program_counter = instruction_register[1];
				jmp_flag = 1;
			} else {
				program_counter += 1;
			}
			break;

			case DSP:
			unsigned short a = *(memory + memory_counter);
			printf("%x\n",a);
			break;

			case LDS:
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

			case NOP:
			break;

			default:
			printf("The VM halted and caught fire.\n");
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
	if(!err_flag && !term_flag) {
		printf("The program halted succesfully.\n");
	} else if(term_flag) {
		printf("Program terminated succesfully.\n");
	}
	return err_flag;
}