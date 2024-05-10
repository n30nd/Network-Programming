#include "stdio.h"
#include "sys/socket.h"
#include "arpa/inet.h"

#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"
#define MAX_MSG_SIZE 1024

int main() {
    //create a socket
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(client_sock < 0){
        perror("socket");
        exit(1);
    }
    //set up the server details
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if(inet_pton(AF_INET, SERVER_IP, &(server.sin_addr)) < 0) {
        perror("inet_pton");
        exit(1);
    }


    //connect to server
    if(connect(client_sock,(struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        exit(1);
    }

    //send a msg to server
    char* msg = "HELLO SERVER, I 'm CLIENT";
    if(send(client_sock, msg, sizeof(msg), 0) < 0) {
        perror("send");
        exit(1);
    }

    //receive msg
    char buffer[MAX_MSG_SIZE];
    memset(buffer, 0, sizeof(buffer));
    if(recv(client_sock, buffer, sizeof(buffer), 0) < 0) {
        perror("recv");
        exit(1);
    }
    printf("Server: %s\n", buffer);

    return 0;
}