#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
//struct sockaddr_in cin,server_addr;
int cid;
char echo[30];
char ch;
//char buffer[30];
int len=0;
int i=0;
cid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
if(cid==-1)
{
perror("Socket Error\n");
}
else
{
printf("Socket Created\n");
struct sockaddr_in addrport;
  addrport.sin_family=AF_INET;
  addrport.sin_port=htons(30000);
  addrport.sin_addr.s_addr=inet_addr("127.0.0.2");
  int status=bind(cid,(struct sockaddr*)&addrport,sizeof(addrport));char filename[50];
	if(status==-1)
  {
   printf("binding unsuccessful!..program terminated!\n");
   return 0;
  }
  printf("binded successfully..\n!");
  struct sockaddr_in client_addr;
  client_addr.sin_family=AF_INET;
  client_addr.sin_port=htons(30173);
  client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
printf("Connected\n");
//char filename[50];
int n=sizeof(client_addr);
char ip[50];
int pid=fork();
if(pid>0)
{
	while(strcmp(ip,"bye")!=0)
	{
		printf("Gonna receive");
		int count=recvfrom(cid,ip,sizeof(ip),0,(struct sockaddr*)&client_addr,(socklen_t*)&n);
		printf("%s",ip);
		if(strcmp(ip,"bye")==0)
		{
			close(cid);
			printf("Disconnected ...\n");
			return 0;
		}
	}
}

else	
{
	while(strcmp(filename,"bye")!=0)
	{
		printf("Send msg:");
		gets(filename);
		int count1=sendto(cid,filename,sizeof(filename),0,(struct sockaddr*)&client_addr,(socklen_t)n);
		if(strcmp(filename,"bye")==0)
		{
			close(cid);
			printf("Disconnected ...\n");
			return 0;
		}
	}
}
}
}