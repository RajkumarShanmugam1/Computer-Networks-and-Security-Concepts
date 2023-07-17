/* UDP Socket - TEMPLATE
 * Client program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define IP   "127.0.0.1"  /* Your IP address */
#define PORT 1234         /* Your port */   

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    
    /* SOCKET */
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }
    printf("SOCKET CREATED\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    /* APPLICATION */
    /* SENT FOR DEMO*/
    sendto(client_socket, "DEMO", strlen("DEMO"), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* CLOSE THE SOCKET */
    if (close(client_socket) == 0) {
        printf("CLIENT SOCKET CLOSED\n");
    } 
    else {
        perror("CLIENT SOCKET CLOSE ERROR");
    }
    return 0;
}
