#include "stdio.h"
enum {SUCCESS, FAIL};
int main(){
    FILE *fptr1, *fptr2;
    char fileName1[] = "lab1.txt";
    char fileName2[] = "lab1w.txt";

    fptr1 = fopen(fileName1, "r");
    fptr2 = fopen(fileName2, "w");
    if(fptr1 == NULL){
        printf("CANNOT OPEN FILE %s\n", fileName1);
        return FAIL;
    }
    else if(fptr2 == NULL){
        printf("CANNOT OPEN FILE %s\n", fileName2);
        return FAIL;
    }
    else {
        int c;
        while((c=fgetc(fptr1)) != EOF){
            fputc(c, fptr2);
            putchar(c);
        }
    }
    return SUCCESS;
}