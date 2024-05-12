#include <stdio.h>

int main() {
    char str[] = "Hello  123 World";
    char string[10];
    int num;

    sscanf(str, "%s %d", string, &num);
    printf("String: %s, Number: %d\n", string, num);

    return 0;
}
