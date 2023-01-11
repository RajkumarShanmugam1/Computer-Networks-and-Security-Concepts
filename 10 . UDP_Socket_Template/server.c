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
    int cnt =0 ;
    int ccid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(ccid == -1){
        perror("creation failed\n");
    }else{
        printf("created\n");
        int len;
        ccin.sin_family=AF_INET;
        ccin.sin_port=htons(12343);
        ccin.sin_addr.s_addr=inet_addr("127.0.0.2");

        cin.sin_family=AF_INET;
        cin.sin_port=htons(12342);
        cin.sin_addr.s_addr=inet_addr("127.0.0.1");
        
        if(bind(ccid,(struct sockaddr*)&ccin,sizeof(ccin)) == -1){
                perror("bind failed");
                exit(1);
        }
        
        //Your Application
        
    int status = close(ccid);
    if(status == -1){
        perror("close failed\n");
    }else{
        printf("closed\n");
    }

    }
return 0;
}
