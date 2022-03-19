// Copyright (c) 2022 Ayush Sharma

// This file contains the VM entry point as well as the command line inteface logic

#include <stdlib.h>
#include <iostream>
#include <string>

#include "comp.hpp"
#include "microvm.hpp"

int main(int argc, char** argv) {
	if(argc == 1) {
		std::cout << INTRO_TEXT << std::endl;
		return 0;
	}
	int err = decodeArgs(argc, argv);
	return err;
}

// Prepares and executes VM
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

// Argument Parser
int decodeArgs(int argc,char** argv) {

	// File names
	std::string fname;
	std::string ofname;

	// Flags
	bool fnameRead = false;
	bool ofnameRead = false;
	bool CompileFlag = false;
	bool OutputFlag = false;
	bool HelpFlag = false;
	bool DebugFlag = false;

	for(int i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			std::string flag = argv[i];
			if(flag == "-d") {
				DebugFlag = true;
			} else if(flag == "-c") {
				CompileFlag = true;
			} else if(flag == "-o") {
				OutputFlag = true;
			} else if (flag == "-h" || flag == "-help") {
				HelpFlag = true;
			} else {
				std::cout << "Invalid flag " << flag << std::endl;
				return 4;
			}
		} else {
			if(OutputFlag && !ofnameRead) {
				ofname = argv[i];
				ofnameRead = true;
			} else if(!fnameRead) {
				fname = argv[i];
				fnameRead = true;
			} else {
				std::cout << "Invalid argument " << argv[i] << std::endl;
				return 4;
			}
		}
	}

	if(CompileFlag && DebugFlag) {
		std::cout << "Cant debug a source file directly" << std::endl;
	} else if(HelpFlag && (CompileFlag || DebugFlag)) {
		std::cout << "Invalid arguments" << std::endl;
		return 10;
	} else if(CompileFlag) {
		if(!OutputFlag) ofname = "a";
		int err = compile(fname,ofname);
		return err;
	} else if(DebugFlag) {
		std::cout << "Debugging " << fname << std::endl;
	}
	
	if(!CompileFlag && !HelpFlag) {
		executeVM(fname,DebugFlag);
	}
	if(HelpFlag) {
		std::cout << HELP_TEXT << std::endl;
	}
	return 0;
}