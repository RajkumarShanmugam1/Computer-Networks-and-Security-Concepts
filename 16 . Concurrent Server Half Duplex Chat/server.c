#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
	int sockfd,ret;
	struct sockaddr_in server_Addr;
	int newSocket;
	socklen_t size_addr;
	struct sockaddr_in newAddr;
	char buffer[1000];
	pid_t child;
	char msg[100];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
	perror("Socket Error\n");
	exit(1);
	}
	printf("Socket is created...\n");
	memset(&server_Addr,'\0',sizeof(server_Addr));
	server_Addr.sin_family=AF_INET;
	server_Addr.sin_port=htons(40000);
	server_Addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	ret=bind(sockfd,(struct sockaddr*)&server_Addr,sizeof(server_Addr));
	if(ret==-1)
	{
	perror("Socket Binding Error\n");
	exit(1);
	}
	printf("Binded \n");
	if(listen(sockfd,2)==0)
	{
		printf("In Listening State....\n");
	}
	else
	{
		perror("Error in listening...\n");
		exit(1);
	}
	while(1)
	{
		newSocket=accept(sockfd,(struct sockaddr*)&newAddr,&size_addr);
		if(newSocket<0)
		{
			exit(1);
			break;
		}
		printf("Connected from %s:%d \n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
		if((child=fork())==0)
		{
		close(sockfd);
		while(1)
		{
			recv(newSocket,buffer,1000,0);
			printf("Message from Client:");
			fputs(buffer,stdout);
			if(strcmp(buffer,"bye")==0)
			{
				send(newSocket,buffer,strlen(buffer),0);
				bzero(buffer,sizeof(buffer));
				printf("Disconnected from %s:%d \n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
				close(sockfd);
				break;
			}
			printf("Enter message:");
			fgets(msg,1000,stdin);
			send(newSocket,msg,strlen(msg),0);
		}
	}
}
close(sockfd);
return 0;
}