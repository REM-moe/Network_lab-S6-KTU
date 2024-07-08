#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
    struct sockaddr_in client, server;

    server.sin_family = AF_INET;
    server.sin_port = 8080;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    int sockt = socket(AF_INET, SOCK_DGRAM, 0);

    int size_server = sizeof(server);
    char buf1[10] = "";
    

    while(1) {
        printf("client: ");
        scanf("%s", buf1);

        sendto(sockt, buf1, sizeof(buf1), 0, (struct sockaddr*)&server, size_server);

        recvfrom(sockt, buf1, sizeof(buf1), 0, (struct sockaddr*)&server, &size_server);

        printf("\n server: %s", buf1);


    }

}