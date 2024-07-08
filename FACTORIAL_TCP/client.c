
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>


int main() {
    struct sockaddr_in client, server;

    server.sin_family = AF_INET;
    server.sin_port = 8080;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int sockt = socket(AF_INET, SOCK_STREAM, 0);

    int client_len = sizeof(client);
    connect(sockt, (struct sockaddr*)&server, sizeof(server));

    int num = 0;
    while(1) {
        printf("enter the number to find factorial:  ");
        scanf("%d",&num);

        send(sockt, &num, sizeof(num), 0);

        recv(sockt, &num, sizeof(num), 0);
        printf("\n factorial is: %d\n", num);
    }

}
