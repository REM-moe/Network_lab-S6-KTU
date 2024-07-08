#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockt = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockt, (struct sockaddr*)&server, sizeof(server));
    printf("Connected to server\n");

    while (1) {
        char buf[1024] = "";
        printf("Enter string to check palindrome: ");
        scanf("%s", buf);

        send(sockt, buf, strlen(buf) + 1, 0);

        recv(sockt, buf, sizeof(buf), 0);
    }

    close(sockt);
    return 0;
}
