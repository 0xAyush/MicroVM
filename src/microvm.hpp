// Copyright (c) 2022 Ayush Sharma

#pragma once

extern "C" {
	#include "vm.h"
	#include "state.h"
}

#include "help.h"

void executeVM(std::string fname,bool debug_mode);
int decodeArgs(int argc, char** argv);