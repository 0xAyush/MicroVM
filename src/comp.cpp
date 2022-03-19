// Copyright (c) 2022 Ayush Sharma

// This file contains code for the MVScript 0.1 compiler

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "comp.hpp"

int compile(std::string fname,std::string ofname) {

	unsigned short program[MAXMEM];
	bool validProgram = true;

	std::string errtext;
	std::ifstream file;
	std::string line;

	file.open(fname);
	int lineNo = 1;
	int put_i = 0; // Bytecode output head
	int eo_program = 0; // End of program i.e. maximum put_i

	while(std::getline(file,line)) {

		//Flags and buffer
		std::string buf = "";
		bool typeNum = false;
		bool typeKink = false;
		bool typeOp = false;
		bool reading = false;

		// Multiline comment flags
		bool multiline = false;
		int lparen = 0;

		for(int i = 0; i < line.length(); i++) {

			char c = line[i];

			//Start of a word
			if(c == '#') {
				typeNum = true;
				reading = true;
				continue;
			} else if(c == '$') {
				typeOp = true;
				reading = true;
				continue;
			} else if(c == '~') {
				typeKink = true;
				reading = true;
				continue;
			}

			// Check if word is not two types at same time
			if(typeNum && typeOp || typeNum && typeKink || typeKink && typeOp) {
				validProgram = false;
				errtext = "Syntax error; Word should be either constant or opcode not both.";
				break;
			}

			// Check if word is valid then store in bytecode
			if(c == ' ' || i == line.length() - 1 || c == '/' || c == '(') { // End of token

				if(i == line.length() - 1 && c != ' '  && c != '/') buf += c; // Because on last charecter buf += c is not yet done, also ' ' and '/' are permissible deviations

				// Ignore all multiline comments, needs exception at
				// beginning otherwise  will not load the word touching '('
				if((!multiline || (lparen == 1 && c =='(')) && c != ')') {
					if(buf != "") { // EOL check as well as empty operator check
					 if(typeNum) { // Number logic
							if(isNumber(buf)) {
								program[put_i] = (unsigned short) std::stoi(buf);
								put_i++;
							} else {
								validProgram = false;
								errtext = "Syntax error; " + buf + " is not a number.";
								break;
							}
						} else if(typeOp){ // Opcode logic
							if(getop(buf) != 0xFF) {
								program[put_i] = getop(buf);
								put_i++;
							} else {
									validProgram = false;
									errtext = "Syntax error; " + buf + " is not an opcode.";
									break;
								}
						} else if(typeKink) { // Kink logic
								if(isNumber(buf)) {
									put_i = std::stoi(buf);
								} else {
									validProgram = false;
									errtext = "Syntax error; " + buf + " is not a number.";
									break;
								}
						}
					} else if(i == line.length() - 1){ // Check if EOL or empty op
						validProgram = false;
						errtext = "Syntax error; empty operator.";
						break;
					}
				}

				typeNum = false;
				typeKink = false;
				typeOp = false;
				reading = false;

				buf = "";
			}

			// Multiline comment logic
			if(c == '(') {
				lparen++;
				multiline = true;
			} if(c == ')') {
				lparen--;
			}

			if(multiline && lparen == 0) {
				multiline = false;
			}

			if(reading) { // After word parsing to prevent space from getting into words
					buf += c;
			}

			if(c == '/') break; // Comment logic

			if(eo_program < put_i) eo_program = put_i;

		}
		if(!validProgram) break;
		lineNo++;
	}

	if(!validProgram) {
		std::cout << "Error in line " << lineNo << std::endl;
		std::cout << errtext << std::endl;
	} else {
		int err = writestate(program,eo_program,(ofname+".bin").c_str());
		if(err > 0) {
			return 5;
		} else {
			std::cout << "Done." << std::endl;
		}
	}

	return 0;
}

// Get operators from opcodes
unsigned short getop(std::string word) {
	if(word == "NXT" || word == "NEXT") return NXT;
	else if(word == "PRV" || word == "PREV") return PRV;
	else if(word == "INC" || word == "+") return INC;
	else if(word == "DEC" || word == "-") return DEC;
	else if(word == "JEZ") return JEZ;
	else if(word == "JNZ") return JNZ;
	else if(word == "DSP") return DSP;
	else if(word == "LDS") return LDS;
	else if(word == "CPZ") return CPZ;
	else if(word == "HLT" || word == "HALT") return HLT;
	else if(word == "JMP" || word == "JUMP" || word == "GOTO") return JMP;
	else if(word == "JMM") return JMM;
	else if(word == "NOP") return NOP;
	else if(word == "HCF") return HCF;
	return 0xFF;
}

// Checks if string is a number
bool isNumber(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}