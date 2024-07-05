#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main() {
    struct sockaddr_in client, server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 8080;

    int sockt = socket(AF_INET, SOCK_DGRAM, 0);

    bind(sockt, (struct sockaddr*)&server, sizeof(server));
    
    int client_size = sizeof(client);
    char buf1[10] = "";

    while(1) {

        recvfrom(sockt, buf1, sizeof(buf1), 0, (struct sockaddr*)&client, &client_size);
        printf("\nclient: %s", buf1);

        scanf("%s", buf1);

        sendto(sockt, buf1, sizeof(buf1), 0, (struct sockaddr*) &client, &client_size);
    }
}