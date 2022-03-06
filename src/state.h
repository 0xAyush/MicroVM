// Copright 2022 Ayush Sharma

#pragma once

typedef struct {
    unsigned short* state_ptr;
    int state_length;
    int err_no;
} state_file;

int writestate(unsigned short* stateptr, int state_size);
state_file readstate();