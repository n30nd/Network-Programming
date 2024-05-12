#include "stdio.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "arpa/inet.h"


int main() {
    //steps in client
    //1. create socket
    //2. connect to server
    //3. send/recv data
    //4. close connection

    int client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_port = htons(8888);

    if(connect(client_sock, (struct sockaddr*)&server , sizeof(server)) == 0) {
            char* msg = "Hello Server, I'm client. this is msg";
            send(client_sock, msg, sizeof(msg), 0);
    }
    else {
        printf("Error connect \n");
    }
    close(client_sock);
    printf("Connection closed\n");
    return 0;

   

}