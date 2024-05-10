#include "stdio.h"
#include "string.h"
//Nhap vao tu stdin 1 chuoi ki tu va loai bo dau cach in ra man hinh 
int main() {
    char s[1024];

    fgets(s, sizeof(s)-1, stdin);

    int i = 0;
    while(0 == 0) {
        while(i<strlen(s) && s[i] == ' ') i++;

        while(i<strlen(s) && s[i] != ' ') {
            printf("%c", s[i]);
            i++;
        }
        printf("\n");
        
        if(i == strlen(s)) break;
    }

    return 0;
}