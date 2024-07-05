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

    char buf1[10] = "", buf2[10] = "";
    while(1) {
        printf("client: ");
        scanf("%s", buf2);

        send(sockt, buf2, sizeof(buf2), 0);

        recv(sockt, buf1, sizeof(buf1), 0);
        printf("\n server: %s", buf1);
    }

}