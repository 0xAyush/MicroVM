// Copyright 2022 Ayush Sharma

// This file contains functions for loading and writing VM memory states

#include <stdio.h>
#include <stdlib.h>
#include "state.h"


int writestate(unsigned short* stateptr, int state_size,const char* fname) {

    FILE* fptr = fopen(fname,"wb");
    if(fptr == NULL) {
        perror("Unable to open file for writing");
        return 1;
    }

    fwrite(stateptr,sizeof(unsigned short),state_size,fptr); // Write file
    fclose(fptr);

    return 0;
}

state_file readstate(const char* fname){

    state_file data;
    data.err_no = 0;

    FILE* fptr = fopen(fname,"rb");
    if(fptr == NULL) {
        perror("Unable to open file for reading");
        data.err_no = 1;
        return data;
    }
    
    fseek(fptr,0L,SEEK_END); // Get file size
    long fsize = ftell(fptr);
    rewind(fptr);

    unsigned short* dataptr = (unsigned short*) malloc(fsize); // Make program memory
    int datalength = fsize/sizeof(unsigned short);
    if(dataptr == NULL) {
        perror("Unable to allocate memory for loading state");
        data.err_no = 2;
        return data;
    }

    fread(dataptr,sizeof(unsigned short),datalength,fptr); // Read file
    fclose(fptr);

    data.state_ptr = dataptr;
    data.state_length = datalength;

    return data;
}