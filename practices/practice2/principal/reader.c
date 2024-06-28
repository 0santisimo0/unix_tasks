#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MSG_SIZE 128

int main() {
    char buffer[MSG_SIZE];
    int pipe1_fd, pipe2_fd;

    pipe1_fd = open("pipe1", O_RDONLY);
    if (pipe1_fd == -1) {
        perror("Error opening pipe1");
        exit(EXIT_FAILURE);
    }

    pipe2_fd = open("pipe2", O_WRONLY);
    if (pipe2_fd == -1) {
        perror("Error opening pipe2");
        close(pipe1_fd);
        exit(EXIT_FAILURE);
    }

    while (read(pipe1_fd, buffer, MSG_SIZE) > 0) {
        printf("Program 2 received: %s", buffer);
        fgets(buffer, MSG_SIZE, stdin);
        write(pipe2_fd, buffer, MSG_SIZE);
    }

    close(pipe1_fd);
    close(pipe2_fd);

    return 0;
}