#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

// UDP SERVER;
// - send frame, receive ack; if ack true, continue else retransmit frame

int main() {
    struct sockaddr_in client, server;
    memset(&client, 0, sizeof(client)); // Initialize client structure

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);  // Port number should be in network byte order

    int sockt = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockt < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (bind(sockt, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    int ack = -1;
    socklen_t client_len = sizeof(client);

    if (recvfrom(sockt, &ack, sizeof(ack), 0, (struct sockaddr*)&client, &client_len) < 0) {
        perror("Initial receive failed");
        exit(EXIT_FAILURE);
    }
    printf("Received initial ack\n");

    int f_no = 0;
    printf("Enter number of frames to be sent: ");
    scanf("%d", &f_no);

    for (int i = 0; i < f_no; i++) {
        do {
            printf("\nSending frame %d...", i);
            if (sendto(sockt, &i, sizeof(i), 0, (struct sockaddr*)&client, client_len) < 0) {
                perror("Send failed");
                exit(EXIT_FAILURE);
            }

            printf("Receiving ack...\n");
            if (recvfrom(sockt, &ack, sizeof(ack), 0, (struct sockaddr*)&client, &client_len) < 0) {
                perror("Receive failed");
                exit(EXIT_FAILURE);
            }
            printf("Received: %d as ack\n", ack);
        } while (ack == -1);
    }

    close(sockt);
    return 0;
}
