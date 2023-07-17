/* UDP Socket - Template
 * Server program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define IP   "127.0.0.1"  /* Your IP address */
#define PORT 1234         /* PORT */

int main() {
    int server_socket;
    char buffer[100];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    /* SOCKET */
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }
    printf("SOCKET CREATED\n");

    /* IP Address and port initialization */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP);//INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    /* BIND */
    if (bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("BIND FAILED");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("BIND CREATED\n");

    /* APPLICATION */
    /* Receive for DEMO Connection*/
    memset(buffer, 0, sizeof(buffer));
    recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_size);
    printf("\nCLIENT : %s\n", buffer);

    /* SOCKET CLOSE */
    if (close(server_socket) == 0) {
        printf("SERVER SOCKET CLOSED\n");
    } 
    else {
        perror("SERVER SOCKET CLOSE ERROR");
    }
    return 0;
}
