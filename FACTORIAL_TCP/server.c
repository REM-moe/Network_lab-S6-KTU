
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int facto(int n) {
  while(n != 0) {
    if(n ==0 || n==1) {
      return 1;
    }
    return n*facto((n-1));
  }
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
    int fact = 0;

        recv(S, &fact, sizeof(fact), 0 );
        printf("client: %d\n" , fact);

        printf("\n server: ");
        fact = facto(fact);
        send(S, &fact, sizeof(fact), 0);

    }
}
