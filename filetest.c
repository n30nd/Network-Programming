#include "stdio.h"
enum {SUCCESS, FAIL};
main() {
    FILE *fptr;
    char filename[] = "haiku.txt";
    int reval = SUCCESS;
    if((fptr = fopen(filename, "r")) == NULL){
        printf("Cannot open %s.\n", filename);
        reval = FAIL;
    }
    else {
        printf("The value of ptr: 0x%p\n", fptr);
        printf("Ready to close the file\n");
        fclose(fptr);
    }
    return reval;
}