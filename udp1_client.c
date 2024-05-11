#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// client steps:
// 1. create socket
// 2. bind
// 3. sendto or recvfrom

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main()
{

    int client_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    SOCKADDR_IN saddr, caddr;

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //send msg to server
    char *msg = "HELLO SERVER< I 'm CLIENT";
    sendto(client_sock, msg, sizeof(msg), 0, (SOCKADDR*)&saddr, sizeof(SOCKADDR_IN));

    //recv msg from server
    char buffer[1024] = {0};
    int clen = sizeof(caddr);
    int r = recvfrom(client_sock, buffer, sizeof(buffer)-1, 0, (SOCKADDR*)&caddr, &clen);

    printf("Received %d bytes from %s\n", r, inet_ntoa(caddr.sin_addr));
    printf("MSG: %s \n", buffer);
    return 0;

}