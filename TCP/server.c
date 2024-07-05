#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void main() {

    int sck = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in client, server;

    server.sin_family = AF_INET;
    server.sin_port = 8080;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sck, (struct sockaddr*) &server, sizeof(server));
    listen(sck, 1);
    int n = sizeof(client);
    int S = accept(sck, (struct sockaddr*)&client, &n);

    char buf1[10] = "", buf2[10] = "" ;
    for (;;) {

        recv(S, buf2, sizeof(buf2), 0 );
        printf("client: %s", buf2);

        printf("\n server: ");
        scanf("%s", buf1);

        send(S, buf1, sizeof(buf1), 0);

    }
}