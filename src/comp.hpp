// Copyright (c) 2022 Ayush Sharma

#pragma once

extern "C" {
	#include "vm.h"
	#include "state.h"
}

int compile(std::string fname,std::string ofname);
bool isNumber(const std::string &s);
unsigned short getop(std::string word);