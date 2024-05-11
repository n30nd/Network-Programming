#include "stdio.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "netdb.h"
#include "string.h"
#include "stdlib.h"
#include "arpa/inet.h"

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main()
{
    // steps:
    // 1. create socket
    // 2. bind socket to address
    // 3. listen for incoming connections
    // 4. accept connection
    // 5. send/recv data
    // 6. close connection

    SOCKADDR_IN sddr, caddr;
    sddr.sin_family = AF_INET;
    sddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    sddr.sin_port = htons(8888);

    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (bind(s, (SOCKADDR *)&sddr, sizeof(sddr)) == 0)
    {
        listen(s, 10);
        int clen = sizeof(SOCKADDR_IN);
        while (1)
        {
            int c = accept(s, (SOCKADDR *)&caddr, &clen);
            if (c < 0)
            {
                printf("Error on accept\n");
                continue;
            }

            while (1)
            {
                char buffer[1024] = {0};
                int received = recv(c, buffer, sizeof(buffer) - 1, 0);
                if (received <= 0)
                {
                    break; // Break the inner loop if client disconnects or an error occurs
                }
                printf("Received from client: %s\n", buffer);
            }

            close(c); // Close the client socket
        }

    }
    else
    {
        printf("Failed to bind\n   ");
    }
    close(s);

    return 0;
}