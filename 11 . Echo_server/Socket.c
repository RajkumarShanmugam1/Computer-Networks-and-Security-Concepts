#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>

int main()
{
   struct sockaddr_in cin;
   struct sockaddr_in ccin;
   int cid,n,byte,resv,snt;
   char value[32],buf[32];
   unsigned int len;
   int i=0;
   cid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(cid == -1)
       perror("socket error");
   else
   {
       printf("creation successful\n");
       cin.sin_family = AF_INET;
       cin.sin_port=htons(30163);
       cin.sin_addr.s_addr=inet_addr("127.0.0.1");
       if(bind(cid,(struct sockaddr *) &cin ,sizeof(cin)) == -1 )
       {
            printf("bind failed\n");
       }else
       {
            printf("binding successful\n");
            int listen1=listen(cid,0);
            if(listen1 == -1){
                 printf("Listen failed\n");
            }else
            {
                 printf("Listen successful\n");
                 int n=sizeof(ccin);
                 int asid = accept(cid,(struct sockaddr *) &ccin , &n);
                 if(asid == -1)
                    printf("not accepted\n");
                 else
                 {
                    printf("Accepted\n");
                    while(1)
                    {
                           resv = recv(asid,buf,30,0);
                           if(strcmp(buf,"bye")==0)
                                break;           
                           if(recv!=0)  
                                printf("\nClient : %s\n",buf);           
                           snt=send(asid,buf,30,0);
                           for(i=0;i<strlen(buf);i++)
                               buf[i] =' ';
                    }
                 }
             }
          }
      }
}
