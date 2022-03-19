// Copyright (c) 2022 Ayush Sharma

// This file contains important text data

#define INTRO_TEXT "MicroVM version 0.1\nCopyright (c) 2022 Ayush Sharma.\n"

#define H_TEXT_1 INTRO_TEXT  "A small VM loosely based on the P'' formal language.\n\n"
#define H_TEXT_2 "Usage MICROVM [-c | -d] [-o] [-h | -help] file.\n\n"
#define H_TEXT_3 "-h | -help      Shows this message.\n"
#define H_TEXT_4 "-c file         Compiles the given MVScript file.\n"
#define H_TEXT_5 "-o bin name     Optional, outputs binary with given filename.\n"
#define H_TEXT_6 "-d              Run given binary in debug mode.\n\n"
#define H_TEXT_7 "MICROVM file    Runs given binary file.\n"
#define H_TEXT_8 "MICROVM -c file Compiles file, outputs as a.bin (default) name.\n"

#define HELP_TEXT H_TEXT_1  H_TEXT_2  H_TEXT_3  H_TEXT_4  H_TEXT_5  H_TEXT_6  H_TEXT_7  H_TEXT_8