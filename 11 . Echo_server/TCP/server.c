/* TCP Socket - ECHO SERVER
 * Server program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT      1234        /* Your port */
#define IP        "127.0.0.1"   /* Your IP address */
#define BACKLOG   5        /* Maximum number of pending connections */
#define BUFF_SIZE 100


int main() {
  int server_socket, client_socket, bind_status, listen_status , reuse, status;
  char buffer[BUFF_SIZE];
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len;

  /* SOCKET */
  server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server_socket == -1) {
    perror("SOCKET CREATION ERROR");
    exit(EXIT_FAILURE);
  }
  printf("SOCKET CREATED\n");
 
  /* IP ADDRESS REUSE OR RELEASE */ 
  reuse = 1;
  if (setsockopt(server_socket , SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    perror("SETSOCKOPT ERROR");
  }

  /* SERVER ADDRESS INITIALIZATION */
  memset(&server_addr, 0, sizeof(server_addr)); /* To avoid potential issues */
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(IP);

  /* BIND */
  bind_status = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (bind_status == -1) {
    perror("BIND ERROR");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
  printf("BIND SUCCESSFUL\n");

  /* LISTEN */
  listen_status = listen(server_socket, BACKLOG);
  if (listen_status == -1) {
    perror("LISTEN ERROR");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
  printf("LISTENING...\n");

  /* Accept incoming connections */
  client_addr_len = sizeof(client_addr);
  client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
  if (client_socket == -1) {
    perror("ACCEPT ERROR");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
  printf("CONNECTION SUCCESS\n");

  /* ECHO APPLICATION */
  while(1){
    status = recv(client_socket, buffer, sizeof(buffer)-1, 0);
    if(status == -1){
        perror("RECEIVE ERROR");
        break;
    } 
    else if(status == 0){
        printf("SERVER CLOSED THE CONNECTION\n");
        break;
    } 
    else{ 
        printf("\nRECEIVED : %s\n", buffer);
        if(strcmp(buffer,"bye")==0){
	    printf("\nSERVER SHUTDOWN\n");
	    break;
	}
	if(send(client_socket, buffer, strlen(buffer), 0) == -1){
            printf("SENT ERROR\n");
	    perror("SEND ERROR");
            break;
        }
        memset(buffer, 0, sizeof(buffer));
    }
  }

  /* Close sockets */
  if (close(client_socket) == 0) {
    printf("CLIENT SOCKET CLOSED\n");
  } else {
    perror("CLIENT SOCKET CLOSE ERROR");
  }
  if (close(server_socket) == 0) {
    printf("SERVER SOCKET CLOSED\n");
  } else {
    perror("SERVER SOCKET CLOSE ERROR");
  }

  return 0;
}
