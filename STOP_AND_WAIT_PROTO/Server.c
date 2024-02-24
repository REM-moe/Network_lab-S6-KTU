#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
int main(){
	printf("\n Waiting for client...\n");
	struct sockaddr_in servaddr,cliaddr;
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	memset(&servaddr,0,sizeof(servaddr));
	memset(&cliaddr,0,sizeof(cliaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(8000);
	bind(sockfd,(const struct sockaddr*)&servaddr,sizeof(servaddr));
	int len=sizeof(cliaddr);
	int frames[100],n;
	recvfrom(sockfd,&n,sizeof(n),0,(struct sockaddr*)&cliaddr,&len);
	printf("\nClient connected successfully.\n");
	printf("\nWaiting for total number of frames..\n");
	recvfrom(sockfd,&n,sizeof(n),0,(struct sockaddr*)&cliaddr,&len);
	int p,ack;
	while(1){
		recvfrom(sockfd,&p,sizeof(n),0,(struct sockaddr*)&cliaddr,&len);
		if(p==-99)
			return 0;
		printf("\nReceived frame-%d",p);
		printf("\nEnter 1 for +ve ack and -1 for -ve ack.\n");
		scanf("%d",&ack);
		sendto(sockfd,&ack,sizeof(n),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	}
	return 0;
}
