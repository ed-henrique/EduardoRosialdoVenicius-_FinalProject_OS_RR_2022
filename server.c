#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server_fn/pipe_io.h"

#define BUFFER_SIZE 4096

#define PORT 4444

int main() {
    int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("\033[34m[+]Server Socket Created Successfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port Number %d.\n", PORT);

    listen(sockfd, 5);
    printf("[+]Listening...\n");

    newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
    printf("[+]Connection with Client was Established.\n\033[0m");
    
    char command[BUFFER_SIZE];
    char output[BUFFER_SIZE];
    
    while (1) {
        recv(newSocket, command, BUFFER_SIZE, 0);

        if (strcmp(command, "") == 0) {
            printf("\033[34m[+]Client Disconnected.\n");
            break;
        }

        char tmp[BUFFER_SIZE];
        strcpy(tmp, command);

        printf("\033[34m[+]Received Command: \033[32m%s\n", tmp);

        command_output(tmp, output);

        send(newSocket, output, strlen(output), 0);
        printf("\033[34m[+]Sent Desired Output.\n");

        bzero(tmp, BUFFER_SIZE);
        bzero(output, BUFFER_SIZE);
        bzero(command, BUFFER_SIZE);
    }
    return 0;
}