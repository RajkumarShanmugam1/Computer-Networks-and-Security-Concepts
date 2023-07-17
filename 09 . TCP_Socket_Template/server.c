/* TCP Socket - Template
 * Server program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 1234        /* Your port */
#define IP "127.0.0.1"   /* Your IP address */
#define BACKLOG 5        /* Maximum number of pending connections */

int main() {
  int server_socket, client_socket, bind_status, listen_status , reuse;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len;

  /* Socket */
  server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 
  /* IP address reuse or release*/ 
  reuse = 1;
  if (setsockopt(server_socket , SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    perror("SETSOCKOPT ERROR");
  }

  if (server_socket == -1) {
    perror("SOCKET CREATION ERROR");
    exit(EXIT_FAILURE);
  }
  printf("SOCKET CREATED\n");

  /* Server address initialization */
  memset(&server_addr, 0, sizeof(server_addr)); /* To avoid potential issues */
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(IP);

  /* Bind */
  bind_status = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (bind_status == -1) {
    perror("BIND ERROR");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
  printf("BIND SUCCESS\n");

  /* Listen */
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

  /* Your application code */

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
