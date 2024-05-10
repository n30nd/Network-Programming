// #include <stdio.h>
// #include <string.h>
// #include <malloc.h>
// typedef char* STRING;

// STRING s = NULL;

// void Append(STRING* v, const STRING x)
// {
//     STRING tmp = *v;
//     int oldLen = tmp == NULL ? 0 : strlen(tmp);
//     int newLen = oldLen + strlen(x) + 1;
//     tmp = (STRING)realloc(tmp, newLen);
//     memset(tmp + oldLen, 0, newLen - oldLen);
//     sprintf(tmp + strlen(tmp), "%s", x);
//     *v = tmp;
// }

// int main()
// {
//     Append(&s, "Xin ");
//     Append(&s, "chao ");
//     Append(&s, "cac ");
//     Append(&s, "ban!");
//     printf("%s", s);
//     free(s);
//     s = NULL;
// }

//viet chuong trinh cho phap nhap them cac xau moi vao xau da cho

#include "stdio.h"
#include "string.h"
#include "malloc.h"

typedef char* STRING;

void Append(STRING* v, const STRING x) {
    STRING tmp = *v;
    int oldLen;
    if (tmp == NULL) {
        oldLen = 0;
    }
    else oldLen = strlen(tmp);

    int lenx = strlen(x);

    tmp = (STRING)realloc(tmp, oldLen + lenx + 1);
    memset(tmp + oldLen, 0, lenx);
    strcpy(tmp + oldLen, x);
    *v = tmp;
}
int main()
{
    STRING s = NULL;
    Append(&s, "Xin ");
    Append(&s, "Chao ");
    Append(&s, "VIET ");
    Append(&s, "Nam ");
    printf("%s", s);
    return 0;
}