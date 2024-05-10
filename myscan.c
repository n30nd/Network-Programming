// // scandir
// // scandir(3) - Linux manual page (man7.org)
// // Directory Entries (The GNU C Library
// // string allocation: Ex3.c

// // Viết 1 chương trình (myscan) nhận tham số từ dòng lệnh sau đó in ra file myscan.html ở cùng thư mục thực thi nội dung các file và thư mục con của đường dẫn truyền vào tham số chương trình.
// // Nội dung ở dạng html, mỗi file/thư mục trên một dòng, tên file viết nghiêng, tên thư mục in đậm

// // Ví dụ khi thực thi chương trình: ./myscan /mnt/c/Temp
// // Thì chương trình sẽ in ra file ./myscan.html nội dung của thư mục /mnt/c/Temp

// #include <stdio.h>
// #include <string.h>
// #include <malloc.h>
// #include <dirent.h>

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

// int compare(const struct dirent** item1, const struct dirent** item2)
// {
//     if ((*item1)->d_type == (*item2)->d_type)
//     {
//         return 0;
//     }else
//     {
//         if ((*item1)->d_type == DT_DIR)
//             return -1;
//         else
//             return 1;
//     }
// }

// // int main(int argc, char** argv)
// // {
// //     if (argc > 1)
// //     {
// //         Append(&s, "<html>");
// //         struct dirent** output = NULL;
// //         int n = scandir(argv[1], &output, NULL, compare);
// //         if (n > 0)
// //         {
// //             //FILE* f = fopen("myscan.html", "wt");
// //             FILE* f = fopen("myscan.html","wb");
// //             for (int i = 0;i < n;i++)
// //             {
// //                 if (output[i]->d_type == DT_REG)
// //                 {
// //                     Append(&s, "<i>");
// //                     Append(&s, output[i]->d_name);
// //                     Append(&s, "</i><br>");
// //                 }
// //                 if (output[i]->d_type == DT_DIR)
// //                 {
// //                     Append(&s, "<b>");
// //                     Append(&s, output[i]->d_name);
// //                     Append(&s, "</b><br>");
// //                 }
// //             }
// //             Append(&s, "</html>");
// //             //fprintf(f, "%s", s);
// //             fwrite(s, sizeof(char), strlen(s), f);
// //             fclose(f);
// //             free(s);
// //             s = NULL;
// //         }else
// //             printf("No item found!\n");
// //     }else
// //         printf("Missing parameter!\n");
// // }

// int main(int argc, char** argv)
// {
//         Append(&s, "<html>");
//         struct dirent** output = NULL;
//         int n = scandir("/mnt/c", &output, NULL, compare);
//         if (n > 0)
//         {
//             //FILE* f = fopen("myscan.html", "wt");
//             FILE* f = fopen("myscan.html","wb");
//             for (int i = 0;i < n;i++)
//             {
//                 if (output[i]->d_type == DT_REG)
//                 {
//                     Append(&s, "<i>");
//                     Append(&s, output[i]->d_name);
//                     Append(&s, "</i><br>");
//                 }
//                 if (output[i]->d_type == DT_DIR)
//                 {
//                     Append(&s, "<b>");
//                     Append(&s, output[i]->d_name);
//                     Append(&s, "</b><br>");
//                 }
//             }
//             Append(&s, "</html>");
//             //fprintf(f, "%s", s);
//             fwrite(s, sizeof(char), strlen(s), f);
//             fclose(f);
//             free(s);
//             s = NULL;
//         }else
//             printf("No item found!\n");

// }

// // #include <stdio.h>
// // #include <arpa/inet.h>

// // int main() {
// //     struct in_addr ip_addr;
// //     ip_addr.s_addr = inet_addr("192.168.1.1");

// //     char *ip_str = inet_ntoa(ip_addr);

// //     printf("IP address: %s\n", ip_str);

// //     return 0;
// // }

// #define _DEFAULT_SOURCE
// #include <dirent.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     struct dirent **namelist;
//     int n;

//     n = scandir("/mnt/c", &namelist, NULL, alphasort);
//     if (n == -1)
//     {
//         perror("scandir");
//         exit(EXIT_FAILURE);
//     }

//     while (n--)
//     {
//         printf("%s\n", namelist[n]->d_name);
//         free(namelist[n]);
//     }
//     free(namelist);

//     exit(EXIT_SUCCESS);
// }

#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "dirent.h"

typedef char *STRING;
void Append(STRING *v, const STRING x)
{
    STRING tmp = *v;
    int oldLen = tmp == NULL ? 0 : strlen(tmp);
    int newLen = oldLen + strlen(x) + 1;
    tmp = realloc(tmp, newLen);
    strcat(tmp + oldLen, x);
    *v = tmp;

}

int compare(const struct dirent **item1, const struct dirent **item2)
{
    if ((*item1)->d_type == (*item2)->d_type)
    {
        return 0;
    }
    else
    {
        if ((*item1)->d_type == DT_DIR)
            return -1;
        else
            return 1;
    }
}
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        STRING s = NULL;
        Append(&s, "<htnl>");
        struct dirent **output = NULL;
        int n = scandir(argv[1], &output, NULL, compare);
        if (n > 0)
        {
            FILE *f = fopen("myscan.html", "wb");

            for (int i = 0; i < n; i++)
            {
                if (output[i]->d_type == DT_REG)
                {
                    Append(&s, "<i>");
                    Append(&s, output[i]->d_name);
                    Append(&s, "</i><br>");
                }
                if (output[i]->d_type == DT_DIR)
                {
                    Append(&s, "<b>");

                    Append(&s, output[i]->d_name);
                    Append(&s, "</b><br>");
                }
            }
            Append(&s, "</html>");
            fwrite(s, sizeof(char), strlen(s), f);
            fclose(f);
            free(s);
            s == NULL;
        }
    }
    else
    {
        printf("Usage: ./myscan <directory>\n");
    }
    return 0;
}