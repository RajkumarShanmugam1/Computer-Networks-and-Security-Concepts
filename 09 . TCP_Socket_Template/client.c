#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
   struct sockaddr_in ccin;
   int ccid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(ccid == -1)
       printf("cresation failed \n");
   else
   {
      ccin.sin_family=AF_INET;
      ccin.sin_port=htons(30163);
      ccin.sin_addr.s_addr=inet_addr("127.0.0.1");  // Your IP Address
      printf("creation successful\n");
      int cnct=connect(ccid,(struct sockaddr * ) &ccin, sizeof(ccin));
      if(cnct == -1)
         printf("Connection failed\n");
      else
      {
         printf("Connection successful\n");
         //Your Application
      }
      int status = close(ccid);
      if(status == 0)
          printf("closed\n");
   }
}
