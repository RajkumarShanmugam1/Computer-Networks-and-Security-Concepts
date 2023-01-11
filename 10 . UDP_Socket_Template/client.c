#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


int main()
{
  struct sockaddr_in cin;
  struct sockaddr_in ccin;
  struct sockaddr_in client;
 //  char dname[30];
 //  char msg[30];
  int i,j;
  int cid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
  if(cid == -1)
  {
        perror("creation failed\n");
  }
  else
  {
        printf("created\n");
        cin.sin_family=AF_INET;
        cin.sin_port=htons(12342);
        cin.sin_addr.s_addr=inet_addr("127.0.0.1");

        ccin.sin_family=AF_INET;
        ccin.sin_port=htons(12343);
        ccin.sin_addr.s_addr=inet_addr("127.0.0.2");

        if(bind(cid,(struct sockaddr*)&cin,sizeof(cin)) == -1)
        {
            close(cid);
            perror("bind failed\n");
        }
        else
        {
            printf("binded\n");
        }
        
        // Your Application
        
    int status = close(cid);
    if(status == -1){
        perror("close failed\n");
    }else{
        printf("closed\n");
    }

    }
return 0;
}
