// ex5
// connect to a server via domain name
// printf address of server 

#include "stdio.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "netdb.h"
#include "string.h"
#include "stdlib.h"
#include "arpa/inet.h"

char dn[1024] = {0};
int main()
{
    struct addrinfo *result = NULL;
    struct addrinfo *tmp = NULL;
    struct sockaddr_in* tmpaddr = NULL;

    char response[1024] = {0};
    int r = 0;
    strcpy(dn, "vnexpress.net");
    getaddrinfo(dn, "http", NULL, &result);
    tmp = result;

    while (tmp != NULL)
    {
        if (tmp->ai_family == AF_INET)
        {
            char ip[1024] = {0};
            tmpaddr = (struct sockaddr_in *)tmp->ai_addr;
            strcpy(ip, (char *)inet_ntoa(tmpaddr->sin_addr));
            printf("%s:%d\n", ip, ntohs(tmpaddr->sin_port));
            break;
        }
        tmp = tmp->ai_next;
    }        

    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int error = connect(s, (struct sockaddr *)&tmpaddr, sizeof(struct sockaddr_in));
    if (error == 0)
    {
        char *welcome = "XIN CHAO";
        send(s, welcome, strlen(welcome), 0);
        r = recv(s, response, sizeof(response)-1, 0);
        printf("Server's response: %s\n", response);
    }
    
    freeaddrinfo(result);
    close(s);
    return 0;
}
