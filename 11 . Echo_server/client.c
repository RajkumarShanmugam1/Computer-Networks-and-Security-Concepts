/* TCP Socket - ECHO SERVER
 * Client program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT      1234       	/* Your port */
#define IP        "127.0.0.1"	/* Your IP address */
#define BUFF_SIZE 100		   /* Size for buffer*/

int main() {
  int client_socket, connect_status, status;
  char buffer[BUFF_SIZE], message[BUFF_SIZE];
  struct sockaddr_in server_addr;

  /* SOCKET */
  client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (client_socket == -1) {
    perror("SOCKET CREATION ERROR");
    exit(EXIT_FAILURE);
  }

  printf("SOCKET CREATED\n");

  /* SERVER ADDRESS INITIALIZATION */
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(IP);

  /* CONNECT */
  connect_status = connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (connect_status == -1) {
    perror("CONNECTION FAILED");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  printf("CONNECTION SUCCESSFUL\n");

  /* ECHO APPLICAION */
  memset(&buffer,0,sizeof(buffer));
  while(1) {
    printf("\nMESSAGE : ");
    scanf("%s",message);
    if(send(client_socket, message, strlen(message), 0) == -1) {
       perror("SEND ERROR");
       break;
    }
    if(strcmp(message,"bye")==0) {
       printf("\nSERVER DISCONNECTED\n");
       break;
    }
    status = recv(client_socket, buffer, sizeof(buffer)-1 ,0);
    if(status == -1) {
       perror("RECEIVE ERROR");
       break;
    } 
    else if(status == 0) {
       printf("SERVER CLOSED THE CONNECTION\n");
       break;
    } 
    else{
       printf("\nREPLY   : %s\n",buffer);
    }
    memset(buffer, 0, sizeof(buffer));
  }

  /* Close socket */
  if(close(client_socket) == 0) {
    printf("SOCKET CLOSED\n");
  }
  else {
    perror("SOCKET CLOSE ERROR");
  }

  return 0;
}
