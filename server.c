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
	char b1[10], b[10];
	s = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(s, (struct sockaddr *) &server, sizeof(server));
	n = sizeof(client);
	while(1) {
		recvfrom(s, b1, sizeof(b1), 0, (struct sockaddr *)&client, &n);
		if(!strcmp(b1,"end"))
			break;
		printf("client:%s\n",b1);
		printf("server");
		scanf("%s",b1);
		sendto(s,b1,sizeof(b1),0,(struct sockaddr *) &client,n);
	}
}
