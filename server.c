#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main() {
	int s, n, sock;
	struct sockaddr_in client, server;
	char buf1[10] = "", buf2[10] = "Hello" ;
	s = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(s, (struct sockaddr *)&server, sizeof(server));

	listen(s, 1);

	n = sizeof(client);
	sock = accept(s, (struct sockaddr *) &client, &n);
	for(;;) {
		recv(sock, buf1, sizeof(buf1), 0);
		if(strcmp(buf1, "end") == 0)
			break;
		printf("\n client: %s", buf1);
		printf("\nserver:");
		scanf("%s",buf2);
		send(sock,buf2,sizeof(buf2),0);
		if(strcmp(buf2,"end") == 0) 
			break;
	}
	close(sock);
	close(s);
}
