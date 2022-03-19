// Copyright 2022 Ayush Sharma

#include <stdlib.h>
#include <iostream>
#include <string>

#include "comp.hpp"

extern "C" {
	#include "vm.h"
	#include "state.h"
}

void executeVM(std::string fname,bool debug_mode);
int decodeArgs(int argc, char** argv);

int main(int argc, char** argv) {
	int err = decodeArgs(argc, argv);
	return err;
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

int decodeArgs(int argc,char** argv) {
	if(argc > 3) {
		std::cout << "Too many arguments max 2" << std::endl;
		return 6;
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
				return 0;
			} else if(arg == "-c") {
				CompileFlag = true;
			} else if(arg == "-d") {
				DebugFlag = true;
			} else {
				std::cout << "Unknown flag '" << arg << "'" << std::endl;
				return 4;
			}
		} else {
			fname = argv[i];
		}
	}
	if(CompileFlag && DebugFlag) {
			std::cout << "Error bad arguments." << std::endl;
	} else if(CompileFlag) {
		int err = compile(fname);
	} else if(DebugFlag) {
		std::cout << "Debugging " << fname << std::endl;
	}
	
	if(!CompileFlag) {
		executeVM(fname,DebugFlag);
	}
	return 0;
}