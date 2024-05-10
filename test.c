// // // #include <stdio.h>
// // // #include <arpa/inet.h>

// // // int main() {
// // //     struct in_addr ip_addr;
// // //     ip_addr.s_addr = inet_addr("192.168.1.1");

// // //     char *ip_str = inet_ntoa(ip_addr);

// // //     printf("IP address: %s\n", ip_str);

// // //     return 0;
// // // }

// // #define _DEFAULT_SOURCE
// // #include <dirent.h>
// // #include <stdio.h>
// // #include <stdlib.h>

// // int main(void)
// // {
// //     struct dirent **namelist;
// //     int n;

// //     n = scandir("/mnt/c", &namelist, NULL, alphasort);
// //     if (n == -1)
// //     {
// //         perror("scandir");
// //         exit(EXIT_FAILURE);
// //     }

// //     while (n--)
// //     {
// //         printf("%s\n", namelist[n]->d_name);
// //         free(namelist[n]);
// //     }
// //     free(namelist);

// //     exit(EXIT_SUCCESS);
// // }




// #include "stdio.h"
// #include "string.h"
// #include "malloc.h"
// #include "dirent.h"

// typedef char* STRING;
// void Append(STRING* v, const STRING x) {
//     STRING tmp = *v;
//     int oldLen = tmp == NULL ? 0 : strlen(tmp);
//     int newLen = oldLen + strlen(x) + 1;
//     tmp = realloc(tmp, newLen);
//     strcat(tmp + oldLen, x );
//     *v = tmp;
//     free(tmp);
// }

// int compare(const struct dirent** item1, const struct dirent** item2) {
//     if ((*item1)->d_type == (*item2)->d_type) {
//         return 0;
//     }
//     else {
//         if((*item1)->d_type == DT_DIR) return -1;
//         else return 1;
//     }
// }
// int main(int argc, char* argv[]) {
//     if(argc > 1) {
//         STRING s = NULL;
//         Append(&s, "<htnl>");
//         struct dirent** output = NULL;
//         int n =  scandir(argv[1], &output, NULL, compare);
//         if(n > 0) {
//             FILE* f= fopen("myscan.html", "wb");

//             for (int i=0;i<n;i++) {
//                 if(output[i]->d_type == DT_REG) {
//                     Append(&s, "<i>");
//                     Append(&s, output[i]->d_name);
//                     Append(&s, "</i><br>");
//                 }
//                 if(output[i]->d_type == DT_DIR) {
//                     Append(&s, "<b>");

//                     Append(&s, output[i]->d_name);
//                     Append(&s, "</b><br>");
//                 }
//             }
//         }


//         Append(&s, "</html>");
//         fwrite(s, sizeof(char), strlen(s), f);
//         fclose(f);
//         free(s);
//         s == NULL;
//     }
//     else {
//         printf("Usage: ./myscan <directory>\n");
//     }
//     return 0;
// }


#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE 4096
int copyfile(const char* source_file_name, const char* destination_file_name, size_t block_size) {
    FILE* source_file = fopen(source_file_name, "rb");
    if (source_file == NULL) {
        printf("Error opening source file\n");
        return 0;
    }

    FILE* dest_file = fwrite(destination_file_name, "wb");
    if (dest_file == NULL) {
        printf("Error opening destination file \n");
        return 0;
    }

    char buffer[BUFFER_SIZE];
    size_t byte_read;
    
    while(byte_read = fread(buffer, sizeof(char), block_size, source_file) > 0) {
        fwrite(buffer, sizeof(char), byte_read, dest_file);
    }

    close(source_file);
    close(dest_file);
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source_file> <destination_file> <block_size>\n");
        return 1;
    }
    else {
        int n = copyfile(argv[1], argv[2], atoi(argv[3]));
        if (n == 1 ) {
            printf("COPY SUCCESSFULLY\n");
        }
        else {
            printf("COPY FAILED\n");
        }
    }
}