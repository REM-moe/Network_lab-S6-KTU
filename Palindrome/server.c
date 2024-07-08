#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockt = socket(AF_INET, SOCK_STREAM, 0);
   
    struct sockaddr_in server, client;

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    bind(sockt, (struct sockaddr*)&server, sizeof(server));

    listen(sockt, 1);

    int cl_size = sizeof(client);
    int sokkt = accept(sockt, (struct sockaddr*)&client, &cl_size);

    while (1) {
        printf("Receiving string from client to check palindrome\n");
        char buf[1024] = "";

        recv(sokkt, buf, sizeof(buf), 0);

        printf("Received %s from client\n", buf);

        int is_palindrome = 1;
        int left = 0;
        int right = strlen(buf) - 1;
        while (left < right) {
            if (buf[left] != buf[right]) {
                is_palindrome = 0;
                break;
            }
            left++;
            right--;
        }

        const char* response = is_palindrome ? "PALINDROME" : "NOT PALINDROME";
        send(sokkt, response, strlen(response) + 1, 0);
    }
}
