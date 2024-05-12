// #include "stdio.h"
// #include "sys/types.h"
// #include "unistd.h"

// void forkexample()
// {   
//     int x = 1;
//     // child process
//     if (fork() == 0)
//     {
//         printf("child has x = %d\n", ++x);
//         printf("child %p\n", &x);
//     }

//     //parent process 
//     else 
//     {
//         printf("parent has x= %d\n", --x);
//         printf("parent %p\n", &x);
//     }
// }
// int main()
// {
//     forkexample();
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int main() {
//     pid_t pid;
//     int status;

//     // Tạo một tiến trình con
//     pid = fork();

//     if (pid < 0) {
//         // Lỗi khi tạo tiến trình con
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         // Code của tiến trình con
//         printf("Child process running...\n");
//         sleep(5); // Giả định tiến trình con làm việc trong 2 giây
//         exit(123); // Kết thúc tiến trình con với mã lỗi 123
//     } else {
//         // Code của tiến trình cha
//         printf("Parent process waiting for child to finish...\n");
        
//         // Chờ đợi cho đến khi tiến trình con kết thúc
//         wait(&status);

//         if (WIFEXITED(status)) {
//             // Nếu tiến trình con kết thúc một cách bình thường
//             printf("Child process terminated with exit status: %d\n", WEXITSTATUS(status));
//         } else {
//             // Nếu có lỗi xảy ra khi kết thúc tiến trình con
//             printf("Child process terminated abnormally.\n");
//         }
//     }

//     return 0;
// }


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int s;
int g_clients[1024];
int g_count = 0;
int pid = 0;

void sig_handler(int signal)
{
    int c = 0;
    printf("Signal received: %d\n", signal);
    FILE* f = fopen("data.txt","rt");
    char buffer[1024] = { 0 };
    fgets(buffer, sizeof(buffer) - 1, f);
    sscanf(buffer, "%d", &c);
    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, sizeof(buffer) - 1, f);
    fclose(f);
    for (int i = 0;i < g_count;i++)
    {
        if (g_clients[i] != c)
        {
            send(g_clients[i], buffer, strlen(buffer), 0);
        }
    }
}

int main()
{
    pid = getpid();
    signal(SIGUSR1, sig_handler);
    SOCKADDR_IN saddr, caddr;
    int clen = sizeof(caddr);
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888);
    saddr.sin_addr.s_addr = 0;
    bind(s, (SOCKADDR*)&saddr, sizeof(saddr));
    listen(s, 10);
    FILE* f = fopen("clients.txt","wt");
    fclose(f);
    while (0 == 0)
    {
        int c = accept(s, (SOCKADDR*)&caddr, &clen);
        printf("A new client accepted\n");
        g_clients[g_count] = c;
        g_count ++;
        if (fork() == 0)
        {
            close(s);
            while (0 == 0)
            {
                char buffer[1024] = { 0 };
                printf("Waiting for data from client\n");
                int r = recv(c, buffer, sizeof(buffer) - 1, 0);
                printf("Received %d bytes from socket %d\n", r, c);
                if (r <= 0)
                {
                    printf("A client has disconnected\n");
                    break;
                }else
                {
                    FILE* f = fopen("data.txt","wt");
                    fprintf(f, "%d\n", c);
                    fprintf(f, "%s", buffer);
                    fclose(f);
                    kill(pid, SIGUSR1);
                }
            }
        }
    }
}