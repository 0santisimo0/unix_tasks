// client_handler.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

// Buffer size for communication
#define BUFFER_SIZE 1024

// Function to handle each client connection
void *handle_client(void *client_sock) {
    int sock = *(int *)client_sock;
    free(client_sock);
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }

        // Handle "getInfo" command
        if (strncmp(buffer, "getInfo", 7) == 0) {
            snprintf(response, BUFFER_SIZE, "Mike's service, v0.1\n");
        } 
        // Handle "getNumberOfPartitions" command
        else if (strncmp(buffer, "getNumberOfPartitions", 21) == 0) {
            FILE *fp = popen("lsblk -l | grep part | wc -l", "r");
            if (fp == NULL) {
                snprintf(response, BUFFER_SIZE, "Error getting number of partitions\n");
            } else {
                fgets(response, BUFFER_SIZE, fp);
                pclose(fp);
            }
        } 
        // Handle "getCurrentKernelVersion" command
        else if (strncmp(buffer, "getCurrentKernelVersion", 23) == 0) {
            FILE *fp = popen("uname -r", "r");
            if (fp == NULL) {
                snprintf(response, BUFFER_SIZE, "Error getting kernel version\n");
            } else {
                fgets(response, BUFFER_SIZE, fp);
                pclose(fp);
            }
        } 
        // Handle "sshdRunning" command
        else if (strncmp(buffer, "sshdRunning", 11) == 0) {
            if (access("/var/run/sshd.pid", F_OK) != -1) {
                snprintf(response, BUFFER_SIZE, "true\n");
            } else {
                snprintf(response, BUFFER_SIZE, "false\n");
            }
        } 
        // Handle unknown command
        else {
            snprintf(response, BUFFER_SIZE, "Unknown command\n");
        }

        send(sock, response, strlen(response), 0);
    }

    close(sock);
    return NULL;
}