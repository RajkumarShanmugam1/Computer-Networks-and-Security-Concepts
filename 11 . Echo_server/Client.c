#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()
{
   struct sockaddr_in ccin;
   int i=0;
   char buf[30];
   int ccid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(ccid == -1)
       printf("cresation failed \n");
   else
   {
      ccin.sin_family=AF_INET;
      ccin.sin_port=htons(30163);
      ccin.sin_addr.s_addr=inet_addr("127.0.0.1");
      printf("creation successful\n");
      int cnct=connect(ccid,(struct sockaddr * ) &ccin, sizeof(ccin));
      if(cnct == -1)
         printf("Connection failed\n");
      else
      {
         printf("Connection successful\n");
         char sent_msg[50];
         buf[0] = 'a';
         while(1)
         {
             printf("Mesg : ");
             scanf("%s",&sent_msg);
             int snt = send(ccid,sent_msg,30,0);
             if(strcmp(sent_msg,"bye")==0)
                   break;
             if(snt == -1)
                 printf("msg transmitted failed\n");
             int resv=recv(ccid,buf,30,0);
             if(resv == -1)
                 printf("msg didnt received\n");
             else
                 printf("Echo : %s\n",buf);
             for(i=0;i<strlen(buf);i++)
                 buf[i]=' ';
         }
       }
       int status = close(ccid);
       if(status == 0)
          printf("closed\n");
   }
}
