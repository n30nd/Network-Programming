#include "stdio.h"
#include ""
int main(){
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int clen;
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888);// ((8888 & 0x00FF) << 8) | (8888 &0xFF00) >> 8)
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bind(s, &saddr, sizeof(saddr));
    listen(s, 10);
    int c = accept(s, &caddr, &clen);
    char* welcome = "Hello world, first TCP server";
    send(c, welcome, strlen(welcome), 0);
    char buffer[1024];
    recv(c, buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);
    close(c);
    close(s);
    return 0;
}