#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
int clientSocket;
struct sockaddr_in server_addr;
char buffer[1000];
int len;
char echo[1000];
clientSocket=socket(AF_INET,SOCK_STREAM,0);
if(clientSocket==-1)
{
	perror("Socket Error\n");
	exit(1);
}
printf("Socket is created...\n");
memset(&server_addr,'\0',sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(40000);
server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int d=connect(clientSocket,(struct sockaddr*)&server_addr,sizeof(server_addr));
printf("%d",d);
if(d<0)
{
	perror("Connection Failed");
	exit(1);
}
printf("Connected to server\n");
while(strcmp(echo,"bye"))
{
	printf("\nEnter message:");
	gets(echo);
	len=strlen(echo);
	int count=send(clientSocket,echo,sizeof(echo),0);
	if(strcmp(echo,"bye")==0)
	{
	int c1=recv(clientSocket,buffer,sizeof(buffer),0);
	if(c1!=-1)
	printf("\nFrom Server: %s",buffer);
	close(clientSocket);
	printf("Disconnected ...\n");
	exit(1);
	break;
	}
	int c1=recv(clientSocket,buffer,sizeof(buffer),0);
	if(c1!=-1)
	printf("\nFrom Server: %s",buffer);
}
close(clientSocket);
return 0;
}


