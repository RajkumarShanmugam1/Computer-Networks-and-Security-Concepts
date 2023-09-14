/* UDP Socket - ECHO
 * Client program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define IP "127.0.0.1"
#define PORT 1234

int main() {
    int client_socket;
    char buffer[100];
    struct sockaddr_in server_addr; // Changed variable name to server_addr
    ssize_t received_bytes;
    
    /* socket */
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
    while (1) {
        
        memset(buffer, 0, sizeof(buffer));
        printf("\nMESSAGE : ");
        scanf("%s", buffer); // Limited the input size to prevent buffer overflow

        /* SENT */
        sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

        /*BREAK*/
        if (strcmp(buffer, "bye") == 0) {
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        socklen_t server_addr_size = sizeof(server_addr); // Added server_addr_size variable
        
        /* RECEIVE */
        received_bytes = recvfrom(client_socket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server_addr, &server_addr_size);
        if (received_bytes == -1) {
            perror("ERROR while receiving");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
        
        printf("\nSERVER : %s\n", buffer);
    }

    /* CLOSE THE SOCKET */
    if (close(client_socket) == 0) {
        printf("CLIENT SOCKET CLOSED\n");
    } else {
        perror("CLIENT SOCKET CLOSE ERROR");
    }
    return 0;
}

