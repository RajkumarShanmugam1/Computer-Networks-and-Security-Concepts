#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(){
    struct sockaddr_in cin;
    struct sockaddr_in ccin;
    char msg[30];
    char receive[100];

    int ccid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(ccid == -1){
        perror("creation failed\n");
    }else{
        printf("Socket created\n");
        ccin.sin_family=AF_INET;
        ccin.sin_port=htons(30163);
        ccin.sin_addr.s_addr=INADDR_ANY;
        int len=sizeof(ccin);
        while(1){
        printf("domain name : ");
        scanf("%s",msg);
        int n = sendto(ccid,msg,sizeof(msg),MSG_CONFIRM,(struct sockaddr*)&ccin,len);
        if(strcmp(msg,"bye")==0)
               break;
        len=sizeof(cin);
        int re=recvfrom(ccid,receive,sizeof(receive),MSG_CONFIRM,(struct sockaddr*)&cin,&len);
        printf("IP  address : %s \n",receive);
    }}
    int status = close(ccid);
    if(status == -1){
        perror("close failed\n");
    }else{
        printf("closed\n");
    }
return 0;
}
