#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main()
{
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace with your server's IP

    if (connect(s, (SOCKADDR *)&saddr, sizeof(saddr)) == 0)
    {
        char buffer[1024] = {0};
        printf("Enter command: ");
        fgets(buffer, sizeof(buffer) - 1, stdin);
        buffer[strlen(buffer) - 1] = 0; // remove newline character

        send(s, buffer, strlen(buffer), 0);

        while (1)
        {
            memset(buffer, 0, sizeof(buffer));
            int r = recv(s, buffer, sizeof(buffer) - 1, 0);
            if (r > 0)
            {
                printf("%s", buffer);
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        printf("FAILED TO CONNECT\n");
    }
    close(s);
    return 0;
}