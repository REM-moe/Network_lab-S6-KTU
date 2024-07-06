#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

// UDP client
// - receive frame, send +1 for ack, -1 for not ack

int main() {
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server)); // Initialize server structure

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);  // Port number should be in network byte order

    int sockt = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockt < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int frame = 0;
    int ack = -1;
    socklen_t _len = sizeof(server);
    
    // Send initial ack to server
    if (sendto(sockt, &ack, sizeof(ack), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Initial send failed");
        close(sockt);
        exit(EXIT_FAILURE);
    }
    printf("Sent initial ack\n");

    while (1) {
        if (recvfrom(sockt, &frame, sizeof(frame), 0, (struct sockaddr*)&server, &_len) < 0) {
            perror("Receive failed");
            close(sockt);
            exit(EXIT_FAILURE);
        }
        printf("Received frame no: %d\nEnter 1 for +ve ack, -1 for -ve ack: ", frame);
        scanf("%d", &ack);

        if (sendto(sockt, &ack, sizeof(ack), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
            perror("Send failed");
            close(sockt);
            exit(EXIT_FAILURE);
        }
    }

    close(sockt);
    return 0;
}
