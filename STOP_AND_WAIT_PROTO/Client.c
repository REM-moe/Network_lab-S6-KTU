#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main() {
	printf("\n Searching For Server\n");
	struct sockaddr_in servaddr;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(8000);
	int n = -1;
	sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	printf("Server Connected Succesfully\n Enter No of Frames: ");

	scanf("%d",&n);
	
	sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	int len, ack;
	for(int i = 0; i<n ; i++) {
		ack = -1;
		do {
			printf("Sending Frame: %d\n", i);
			sendto(sockfd, &i, sizeof(n), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
			printf("Waiting Ack!\n");
			recvfrom(sockfd, &ack, sizeof(n), 0, (struct sockaddr*)&servaddr, &len);
			if(ack == -1)
				printf("Negative ACK Recived\n");
		}while(ack == -1);
	}
	n = -99;
	sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	printf("All Frames Sent Succesfully\n");
	close(sockfd);
	return 0;
}
