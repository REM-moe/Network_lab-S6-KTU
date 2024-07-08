
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int isarmstrong(int n) {
    int original = n, sum = 0, digits = 0, temp = n;
    // Calculate the number of digits
    while (temp != 0) {
        temp /= 10;
        digits++;
    }
    temp = n;
    // Calculate the sum of the digits raised to the power of the number of digits
    while (temp != 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < digits; i++) {
            power *= digit;
        }
        sum += power;
        temp /= 10;
    }
    return sum == original;
}

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

    for (;;) {

        char msg[10] = "NOT ARM";
        int arm = 0;
        recv(S, &arm, sizeof(arm), 0 );
        printf("client: %d\n" , arm);

        printf("\n server: ");
        int isarm = isarmstrong(arm);
        if(isarm) {
            strcpy(msg,"YES ARM");
            send(S, msg, sizeof(msg), 0);
        }
        send(S, msg, sizeof(msg), 0);

    }
}
