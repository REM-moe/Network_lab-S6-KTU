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
	char buf1[10] = "", buf2[10] = "palindrome" ;
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
		printf("\nserver:");
		int l = 0;
		int h = strlen(buf1) - 1;
		while (h > l){
			if (buf1[l++] != buf1[h--]){
                char msg[20] = "Not palindrome";
                send(sock,msg,sizeof(msg),0);;
            }
        }

		send(sock,buf2,sizeof(buf2),0);
		if(strcmp(buf2,"end") == 0) 
			break;
	}
	close(sock);
	close(s);
}
