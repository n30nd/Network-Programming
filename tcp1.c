// Write a TCP client, find IP of a host (by its name),
//  connect to a service port (ex.: 80), 
//  send a message to the server, receive and 
//  print out the server’s response.


#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "netdb.h"
#include "netinet/in.h"
#include "string.h"
int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Usage: %s hostname port \n", argv[0]);
        return 1;
    }

    char* hostname = argv[1];
    int port = atoi(argv[2]);

    // Resolve the IP address of the host
    struct hostent *host = gethostbyname(hostname);
    if(host == NULL) {
        printf("Error: %s is not a valid hostname\n", hostname);
        return 1;
    }

    //Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        printf("Error: Could not create socket\n");
        return 1;
    }

    //Set up the server details
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr = *((struct in_addr *)host->h_addr_list[0]);

    //Connect to the server
    if( connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error: Could not connect to server\n");
        return 1;
    }

    //send a messgae to server
    char *msg = "HELLO SERVER!!!!!!!!!!!!!!";
    
    if(send(sock, msg, strlen(msg), 0) < 0) {
        printf("Error: Could not send meg to sv\n");
        return 1;
    }

    char res[4096];
    memset(res, 0, sizeof(res));

    if(recv(sock, res, sizeof(res), 0) < 0) {
         printf("Error: Could not recv meg to sv\n");
        return 1;
    }

    printf("Server 's response: %s\n", res);

    close(sock);
    return 0;

    }