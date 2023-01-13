#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
  struct sockaddr_in ccin;
  char buf[100];
  int ccid=socket(PF_INET, SOCK_STREAM , IPPROTO_TCP);
  if(ccid ==-1)
    printf("Creation failed\n");
  else{
    printf("creation successful\n");
    ccin.sin_family=AF_INET;
    ccin.sin_port=htons(30163);
    ccin.sin_addr.s_addr = inet_addr("127.0.0.1");
    int cnct = connect(ccid,(struct sockaddr*)&ccin,sizeof(ccin));
    if(cnct == -1)
      printf("connection failed");
    else{
        FILE *fp;
        char file[30];
        char name[30];
      printf("connection successfull \n");
      printf("File Name : ");
        scanf("%s",name);
        send(ccid,name,sizeof(name),0);
        recv(ccid,buf,sizeof(buf),0);
        if(strcmp(buf,"file not found")==0){
                        printf("\n- -File Not Found - -\n");
                }
        else{
                printf("\n - - File Found- - \n");
                printf("New File : ");
                scanf("%s",file);
                send(ccid,file,sizeof(file),0);
                fp=fopen(file,"w");
        while(recv(ccid,buf,sizeof(buf),0)){
                fprintf(fp,"%s",buf);
        }
        fclose(fp);
        printf("- - File Downloaded - -\n");
        }
      }
     int status = close(ccid);
     if(status == 0)
        printf("closed\n");
  }
  printf("\n");
  return 0;
}
