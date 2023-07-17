/* TCP Socket - Template
 * Client program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 1234       /* Your port */
#define IP "127.0.0.1"  /* Your IP address */

int main() {
  int client_socket, connect_status;
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
  connect_status = connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
  if (connect_status == -1) {
    perror("CONNECTION FAILED");
    close(client_socket);
    exit(EXIT_FAILURE);
  }
  printf("CONNECTION SUCCESSFUL\n");

  /* Your application code */

  /* SOCKET CLOSE */
  if (close(client_socket) == 0) {
    printf("SOCKET CLOSED\n");
  }else {
    perror("SOCKET CLOSE ERROR");
  }

  return 0;
}
