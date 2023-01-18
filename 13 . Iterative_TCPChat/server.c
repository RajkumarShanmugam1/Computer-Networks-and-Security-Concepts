#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>

int main(){
 struct sockaddr_in cin;
 struct sockaddr_in ccin;
 int cid,n,byte,cnt=0;
 char echobuf[30],buf[30],msg[30];
 unsigned int len;
 int i=0;
 cid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(cid == -1)
   perror("socket error");
  else{
   printf("creation successful\n");
   cin.sin_family = AF_INET;
   cin.sin_port=htons(12345);
   cin.sin_addr.s_addr=htonl(INADDR_ANY);
   if( bind(cid,(struct sockaddr *) &cin ,sizeof(cin)) == -1 ){
    printf("bind failed\n");
   }else{
    printf("binding successful\n");
    int listen1=listen(cid,0);
    if(listen1 == -1){
     printf("Listen failed\n");
    }else{
     printf("Listen successful\n");
     for(;;){
        int n=sizeof(ccin);
     int asid = accept(cid,(struct sockaddr *) &ccin , &n);
     if(asid == -1){
      printf("not accepted\n");
     }else {
      printf("Accepted\n");
        int pid = fork();
        if(pid == 0){
        while(1){
                recv(asid,buf,sizeof(buf),0);
                printf("receive : %s\n",buf);
                if(strcmp(buf,"bye")==0){
                        printf("Echo done\n\n");
                        break;
                }else{
                        printf("Enter message : ");
                        gets(msg);
                        send(asid,msg,sizeof(msg),0);
                }
                if(strcmp(msg,"END") == 0){
                        cnt++;
                        break;
                }
                if(strcmp(msg,"BYE") == 0){
                        break;
                }
                for(i=0;i<strlen(buf);i++){
                        buf[i]=' ';
                }
        }
        }else {
                close(asid);
        }
        }

        if(cnt != 0){
                break;
        }
        }
        }
   }
  int status = close(cid);
  if(status == 0)
   printf("closed");
  }
return 0;
}
