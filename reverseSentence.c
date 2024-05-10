// // Viết chương trình cho phép người dùng nhập một câu dưới dạng đối số dòng lệnh (mỗi từ trong câu là một đối số). Chương trình hiển thị nội dung câu đảo ngược của câu đã nhập.
// // VD: ./inverse I love HUST
// // Cho kết quả: HUST love I

// #include "stdio.h"
// #include "stdlib.h"
// #include "string.h"
// typedef char* STRING;

// void Append(STRING* v, const STRING x) {
//     STRING tmp = *v;
//     int oldLen;
//     if (tmp == NULL) {
//         oldLen = 0;
//     }
//     else oldLen = strlen(tmp);

//     int lenx = strlen(x);

//     tmp = (STRING)realloc(tmp, oldLen + lenx + 1);
//     memset(tmp + oldLen, 0, lenx);
//     strcpy(tmp + oldLen, x);
//     *v = tmp;
// }

// void reverseSentence(char **v)
// {
//     int len = strlen(*v);
//     char* tmp = (char*)malloc(sizeof(char) * (len+1));
//     int i = len - 1;
//     int j = len - 1;
//     STRING* out = NULL;
//     while(0 == 0) {
//         while(i >= 0 && *v[i] != ' ') {
//             i--;
//         }
//         if(i<0) break;
//         else {
//             STRING addS;
//             strncpy(addS, *v + i + 1, j-i);
//             Append(out, addS);
//             Append(out, " ");
//         }
//         i = i-1;
//         j = i;
//     }
//     *v = *out;
// }

// int main(int argc, char *argv[])
// {
//     char *s = argv[1];
//     reverseSentence(&s);
//     printf("%s\n", s);
//     return 0;
// }

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void Append(char **v, const char *x)
{
    if (*v == NULL)
    {
        *v = (char *)malloc(strlen(x) + 1);
        strcpy(*v, x);
    }
    else
    {
        *v = (char *)realloc(*v, strlen(*v) + strlen(x) + 1);
        strcat(*v, x);

    }
}

void reverseSentence(char **v)
{
    int len = strlen(*v);
    char *tmp = (char *)malloc(sizeof(char) * (len + 1));
    int i = len - 1;
    int j = len - 1;
    char *out = NULL;
    while (i >= 0)
    {
        while (i >= 0 && (*v)[i] != ' ')
        {
            i--;
        }
        if (i < 0)
        {   
            char *addS = (char *)malloc(sizeof(char) * (j - i));
            strncpy(addS, (*v) + i + 1, j - i);
            addS[j - i] = '\0'; // Null terminator
            Append(&out, addS);

            break;
        }
        else
        {
            char *addS = (char *)malloc(sizeof(char) * (j - i));
            strncpy(addS, (*v) + i + 1, j - i);
            addS[j - i] = '\0'; // Null terminator
            Append(&out, addS);
            Append(&out, " ");
        }
        i = i - 1;
        j = i;
    }
    *v = out;
    free(tmp);
}

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         printf("Usage: %s <sentence>\n", argv[0]);
//         return 1;
//     }

//     char *s = argv[1];
//     s = "I LOVE HUST";
//     reverseSentence(&s);
//     printf("%s\n", s);
//     free(s); // Remember to free memory allocated by realloc in reverseSentence
//     return 0;
// }

int main()
{
    
    char *s = "I LOVE HUST";
    reverseSentence(&s);
    printf("%s\n", s);
    free(s); // Remember to free memory allocated by realloc in reverseSentence
    return 0;
}
