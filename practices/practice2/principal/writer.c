#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MSG_SIZE 128

int main() {
    char buffer[MSG_SIZE];
    int pipe1_fd, pipe2_fd;

    // Open named pipes
    pipe1_fd = open("pipe1", O_WRONLY);
    if (pipe1_fd == -1) {
        perror("Error opening pipe1");
        exit(EXIT_FAILURE);
    }

    pipe2_fd = open("pipe2", O_RDONLY);
    if (pipe2_fd == -1) {
        perror("Error opening pipe2");
        close(pipe1_fd);
        exit(EXIT_FAILURE);
    }

    // Read from stdin and write to pipe1
    while (fgets(buffer, MSG_SIZE, stdin)) {
        write(pipe1_fd, buffer, MSG_SIZE);
        read(pipe2_fd, buffer, MSG_SIZE);
        printf("Program 1 received: %s", buffer);
    }

    // Close pipes
    close(pipe1_fd);
    close(pipe2_fd);

    return 0;
}