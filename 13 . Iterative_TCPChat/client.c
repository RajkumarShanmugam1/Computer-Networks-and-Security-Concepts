#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
 struct sockaddr_in ccin;
 int i=0;
 char buf[30];
 int ccid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
 if(ccid == -1){
  printf("creation failed \n");
 }else{
  ccin.sin_family=AF_INET;
  ccin.sin_port=htons(12345);
  ccin.sin_addr.s_addr=inet_addr("127.0.0.1");
  printf("creation successful\n");
  int cnct=connect(ccid,(struct sockaddr * ) &ccin, sizeof(ccin));
  if(cnct == -1){
   printf("Connection failed\n");
  }else{
   printf("Connection successful\n");
   char sent_msg[30];
        while(1){
                printf("Enter msg : ");
                gets(sent_msg);
                int snt = send(ccid,sent_msg,30,0);
                if(strcmp(sent_msg,"bye")==0)
                        break;
                int resv=recv(ccid,buf,30,0);
             if(resv == -1)
                 printf("msg didnt received\n");
             else{
                if((strcmp(buf,"BYE") == 0) || (strcmp(buf,"END") == 0)){
                    printf("End of chat\n");
                    break;
                }
                 printf("Received msg  : %s\n",buf);
             }
        }
   }
   int status = close(ccid);
   if(status == 0)
    printf("closed\n");
  }
}

