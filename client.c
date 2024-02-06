#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main() {
	struct sockaddr_in server, client;
	int s, n;
	char b1[10], b2[10];
	s = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	n = sizeof(server);
	while(1) {
		printf("\nclient: ");
		scanf("%s",b2);
		sendto(s, b2, sizeof(b2), 0, (struct sockaddr * ) &server, n);
		if(!strcmp(b2, "end"))
			break;
		recvfrom(s,b1,sizeof(b1),0,NULL,NULL);
		printf("\nserver:%s\n",b1);
	}
}

