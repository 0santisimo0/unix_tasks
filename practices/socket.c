#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP "127.0.0.1"
#define PORT 9595
#define MESSAGE_SIZE 128

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    char message[MESSAGE_SIZE];

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("Failed to create socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &server_addr.sin_addr);

    int connect_status = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_status == -1)
    {
        close(client_fd);
        perror("Failed to connect to server");
        return 1;
    }

    printf("Enter a message: ");
    fgets(message, MESSAGE_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';

    if (write(client_fd, message, strlen(message) + 1) == -1)
    {
        close(client_fd);
        perror("Failed to send message");
        return 1;
    }

    close(client_fd);
    return 0;
}