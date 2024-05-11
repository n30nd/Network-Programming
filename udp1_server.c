// Viết một UDP server:
// Nhận message từ một client bất kỳ
// Lưu các địa chỉ IP của client lại vào một danh sách
// Mỗi lần nhận một message server chuyển tiếp message này đến tất cả các client đã lưu (trừ chính client vừa gửi)

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// steps of server in  UDP:
// 1. create socket
// 2. bind
// 3. recvfrom   //different from TCP is recv
// 4. sendto     //different from TCP is send

int g_count = 0;
struct sockaddr_in* g_addr = NULL;
int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8000);
    saddr.sin_addr.s_addr = 0;


    if(bind(s, (struct sockaddr*)&saddr, sizeof(saddr)) == 0) {
        printf("THIS IS SERVER \n");
        while(0 == 0) {
            char buffer[1024] = { 0 };
            int clen = sizeof(caddr);
            int r = recvfrom(s, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&caddr, &clen );

            int found = 0;
            for(int i=0; i<g_count;i++) {
                if(g_addr[i].sin_addr.s_addr == caddr.sin_addr.s_addr) {
                    found = 1;
                    break;
                }
            }

            if(found == 0) {
                g_addr = (struct sockaddr_in*)realloc(g_addr, (g_count+1));
                g_addr[g_count] = caddr;
                g_count += 1;
            }
            printf("Received %d bytes from %s\n", r, inet_ntoa(caddr.sin_addr));
            printf("MSG: %s \n", buffer);
            for(int i=0;i<g_count;i++) {
                if(g_addr[i].sin_addr.s_addr != caddr.sin_addr.s_addr) {
                    sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr*)(g_addr + i), sizeof(struct sockaddr_in));
                }
                 //sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&g_addr[i], sizeof(struct sockaddr_in));
            }
            }
    }
    else {
        printf("FAIL TO BIND \n");
    }
    close(s);
    return 0;

}
