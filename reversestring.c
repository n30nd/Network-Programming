#include "stdio.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Wrong input\n");
        printf("CORRECT FORMAT <STRING> <STRING> ...\n");
        return 1;
    }
    for(int i=argc-1;i>=1;i--){
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}