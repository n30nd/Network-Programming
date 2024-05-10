// Write a TCP server listening at port 8888,
// send a message “Welcome to my first TCP server”
// when never a client connect to it then wait for a message from the client and
// print the received message to the console, close the socket.

#include "stdio.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "arpa/inet.h"

int main()
{
    int port = 8888;

    // create a socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < -0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // set up the serever details
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to the port
    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    };

    // listen for connections
    if (listen(server_sock, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", port);

    // acept a conncetion
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);

    int client_sock = accept(server_sock, (struct sockaddr *)&client, &client_size);
    if (client_sock < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // send msg to client
    char *msg = "WELCOME TO MY SERVER KKKKK";
    if (send(client_sock, msg, sizeof(msg), 0) < 0)
    {
        perror("send");
        exit(EXIT_FAILURE);
    };

    // receive msg form client
    char res[4096];
    memset(res, 0, sizeof(res));
    if (recv(client_sock, res, sizeof(res), 0) < 0)
    {
        perror("recv");
        exit(EXIT_FAILURE);
    };

    printf("Client 's msg: %s\n", res);

    close(client_sock);
    close(server_sock);
    return 0;
}