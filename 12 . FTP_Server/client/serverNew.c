#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
int main(){
  struct sockaddr_in sin;
  struct sockaddr_in ccin;
  int sid=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sid == -1)
    printf("Creation failed\n");
  else{
    printf("Creation successful\n");
    sin.sin_family=AF_INET;
    sin.sin_port=htons(30161);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(sid,(struct sockaddr*)&sin,sizeof(sin)) == -1)
       printf("bind failed\n");
    else{
       printf("binded successfully\n");
       int listen1 = listen(sid,0);
       if(listen1 == -1)
           printf("listen failed\n");
       else{
           printf("listen succesfull\n");
           int n=sizeof(ccin);
           int asid = accept(sid,(struct sockaddr*)&ccin, &n);
           if(asid ==-1)
               printf("not accepted\n");
           else{
             char msg[30];
             char buf[100];
             printf("accepted\n");
             recv(asid,msg,sizeof(msg),0);
             FILE *fp;
             fp=fopen(msg,"r");
             if(fp == NULL)
                send(asid,"file not found",sizeof("file not found"),0);
             else{
               
                 send(asid,"file found",sizeof("file found"),0);
                recv(asid,msg,sizeof(msg),0);
                while(fgets(buf,sizeof(buf),fp)){
                        send(asid,buf,sizeof(buf),0);
                }
                printf("Transmittion Success\n"); 
                fclose(fp);
             }
           }
        }
     }
     int status = close(sid);
     if(status == 0)
        printf("closed\n");
  }
  printf("\n");
  return 0;
}
