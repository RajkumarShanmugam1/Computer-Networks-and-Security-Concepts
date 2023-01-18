#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
//struct sockaddr_in cin,client_addr;
int sid;
char MAC[50];
char *string;
int size=50;
string=(char*)malloc(size);
char getip[50];
int i,count=0;
sid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
if(sid==-1)
{
perror("Socket Error\n");
}
else
{
printf("\nSocket Created");
struct sockaddr_in addrport;
  addrport.sin_family=AF_INET;
  addrport.sin_port=htons(30173);
  addrport.sin_addr.s_addr=inet_addr("127.0.0.1");
  int status=bind(sid,(struct sockaddr*)&addrport,sizeof(addrport));
  if(status==-1)
  {
   printf("\nbinding unsuccessful!..program terminated!");
   return 0;
  }
  printf("\nbinded successfully..!");
  struct sockaddr_in client_addr;
  client_addr.sin_family=AF_INET;
  client_addr.sin_port=htons(30000);
  client_addr.sin_addr.s_addr=inet_addr("127.0.0.2");
  socklen_t  n=sizeof(client_addr);
char ip[50],filename[50];
int pid=fork();
if(pid==0)
{
	while(strcmp(ip,"bye")!=0)
	{
		printf("will receive");
		int count=recvfrom(sid,ip,sizeof(ip),0,(struct sockaddr*)&client_addr,(socklen_t*)&n);
		printf("%s",ip);printf("%s",ip);
		if(strcmp(ip,"bye")==0)
		{
			close(sid);
			printf("Disconnected ...\n");
			return 0;
		}
	}
}
else	
{
	while(strcmp(filename,"bye")!=0)
	{
		printf("Enter msg:");
		gets(filename);
		int count1=sendto(sid,filename,sizeof(filename),0,(struct sockaddr*)&client_addr,(socklen_t)n);
		if(strcmp(filename,"bye")==0)
		{
			close(sid);
			printf("Disconnected ...\n");
			return 0;
		}
	}
}
}
}
