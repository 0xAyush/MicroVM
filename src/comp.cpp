/* Compiler for MicroVM */
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "comp.hpp"

extern "C" {
	#include "vm.h"
	#include "state.h"
}

int compile(std::string fname) {

	unsigned short program[MAXMEM];
	bool validProgram = true;

	std::string errtext;
	std::ifstream file;
	std::string line;

	file.open(fname);
	int lineNo = 0;
	int put_i = 0;
	while(file >> line) {

		std::string buf = "";
		bool typeNum = false;
		bool typeOp = false;
		bool reading = false;

		for(int i = 0; i < line.length(); i++) {
			
			char c = line[i];

			if(reading) {
				buf += c;
			}


			if(c == '#') {
				typeNum = true;
				reading = true;
			} else if(c == '$') {
				typeOp = true;
				reading = true;
			}

			if(typeNum && typeOp) {
				validProgram = false;
				errtext = "Syntax error; Word should be either constant or opcode not both.";
				break;
			}

			if(c == ' ' || i == line.length() - 1) {

				if(buf != "") {
					if(typeNum) {
						if(isNumber(buf)) {
							program[put_i] = (unsigned short) std::stoi(buf);
							put_i++;
						} else {
							validProgram = false;
							errtext = "Syntax error; " + buf + " is not a number.";
							break;
						}
					} else {
						if(getop(buf) != 0xFF) {
							program[put_i] = getop(buf);
							put_i++;
						}
					}
				}

				typeNum = false;
				typeOp = false;
				reading = false;

				buf = "";
			}

		}
		if(!validProgram) break;
		lineNo++;
	}

	if(!validProgram) {
		std::cout << "Error in line " << lineNo << std::endl;
		std::cout << errtext << std::endl;
	} else {
		std::string nfname = fname.substr(0,fname.length()-4) + ".bin";
		int err = writestate(program,put_i,(nfname).c_str());
		if(err > 0) {
			return 5;
		} else {
			std::cout << "Output saved as "<< nfname << std::endl;
		}
	}

	return 0;
}

unsigned short getop(std::string word) {
	if(word == "NXT") return NXT;
	else if(word == "PRV") return PRV;
	else if(word == "INC") return INC;
	else if(word == "DEC") return DEC;
	else if(word == "JEZ") return JEZ;
	else if(word == "JNZ") return JNZ;
	else if(word == "DSP") return DSP;
	else if(word == "LDS") return LDS;
	else if(word == "CPZ") return CPZ;
	else if(word == "HLT") return HLT;
	else if(word == "JMP") return JMP;
	else if(word == "JMM") return JMM;
	else if(word == "NOP") return NOP;
	else if(word == "HCF") return HCF;
	return 0xFF;
}

bool isNumber(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}