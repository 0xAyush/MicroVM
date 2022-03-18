// Copright 2022 Ayush Sharma

#include <stdlib.h>
#include <iostream>
#include <string>
extern "C" {
	#include "vm.h"
	#include "state.h"
}

void executeVM(std::string fname,bool debug_mode);
void decodeArgs(int argc, char** argv);

int gErr = 1;

int main(int argc, char** argv) {
	decodeArgs(argc, argv);
	return gErr;
}

void executeVM(std::string fname,bool debug_mode) {
	state_file sf = readstate(fname.c_str());
	if(sf.err_no > 0) {
		exit(sf.err_no);
	}
	char debug_flag = 0;
	if(debug_mode) {
		debug_flag = 1;
	}
	int mvm = microvm(sf.state_ptr,sf.state_length,debug_flag);
	if(mvm > 0) {
		exit(2 + mvm);
	}
}

void decodeArgs(int argc,char** argv) {
	if(argc > 3) {
		std::cout << "Too many arguments max 2" << std::endl;
		return;
	}

	std::string fname;
	bool CompileFlag = false;
	bool DebugFlag = false;

	for(int i = 1; i < argc; i++) {
		std::cout << argv[i] << std::endl;
		if(argv[i][0] == '-') {
			std::string arg = argv[i];
			if(arg == "-help") {
				std::cout << "Help." << std::endl;
				return;
			} else if(arg == "-r") {
				CompileFlag = true;
			} else if(arg == "-d") {
				DebugFlag = true;
			} else {
				std::cout << "Unknown flag '" << arg << "'" << std::endl;
				return;
			}
		} else {
			fname = argv[i];
		}
	}
	if(CompileFlag && DebugFlag) {
			std::cout << "Error bad arguments." << std::endl;
	} else if(CompileFlag) {
		std::cout << "Compiling " << fname << std::endl;
	} else if(DebugFlag) {
		std::cout << "Debugging " << fname << std::endl;
	}
	
	if(!CompileFlag) {
		executeVM(fname,DebugFlag);
	}
	gErr = 0;
}