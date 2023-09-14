/* UDP Socket - ECHO
 * Server program
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
    int server_socket;
    char buffer[100];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size = sizeof(client_addr); // Corrected the line

    /* SOCKET */
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }
    printf("SOCKET CREATED\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP);//INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    /* BIND */
    if (bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("BIND CREATED\n");

    /* APPLICATION */
    while (1) {
        
        //Receive
        memset(buffer, 0, sizeof(buffer));
        recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_size);
        printf("\nCLIENT : %s\n", buffer);
        
        if (strcmp(buffer, "bye") == 0) { // Changed the condition to check for zero (false)
            break;
        }
        
        //SENT
        sendto(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, client_addr_size);
    }

    /* SOCKET CLOSE */
    if (close(server_socket) == 0) { // Changed the condition to check for zero (success)
        printf("SERVER SOCKET CLOSED\n");
    } else {
        perror("SERVER SOCKET CLOSE ERROR");
    }
    return 0;
}
