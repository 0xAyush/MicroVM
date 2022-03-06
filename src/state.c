#include <stdio.h>
#include <stdlib.h>
#include "state.h"


int writestate(unsigned short* stateptr, int state_size) {

    FILE* fptr = fopen("state.dat","wb");
    if(fptr == NULL) {
        perror("Unable to open state.dat for writing");
        return 1;
    }

    fwrite(stateptr,sizeof(unsigned short),state_size,fptr);
    fclose(fptr);

    return 0;
}

state_file readstate(){

    state_file data;
    data.err_no = 0;

    FILE* fptr = fopen("state.dat","rb");
    if(fptr == NULL) {
        perror("Unable to open state.dat for reading");
        data.err_no = 1;
        return data;
    }
    
    fseek(fptr,0L,SEEK_END);
    long fsize = ftell(fptr);
    rewind(fptr);

    unsigned short* dataptr = (unsigned short*) malloc(fsize);
    int datalength = fsize/sizeof(unsigned short);
    if(dataptr == NULL) {
        perror("Unable to allocate memory for loading state");
        data.err_no = 2;
        return data;
    }

    fread(dataptr,sizeof(unsigned short),datalength,fptr);
    fclose(fptr);

    data.state_ptr = dataptr;
    data.state_length = datalength;

    return data;
}