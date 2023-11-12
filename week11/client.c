#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_BUFFER_SIZE 200000

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd, portno;
    struct sockaddr_in serv_addr;
    char filename[MAX_FILENAME_LENGTH];
    char buffer[MAX_BUFFER_SIZE];

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        error("ERROR converting server IP");
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    while (1) {
        printf("File Name: ");
        bzero(filename, MAX_FILENAME_LENGTH);
        fgets(filename, MAX_FILENAME_LENGTH, stdin);

        // Remove newline character
        filename[strcspn(filename, "\n")] = 0;

        if (strcmp(filename, "quit") == 0) {
            printf("Exiting...\n");
            break;
        }

        FILE *file = fopen(filename, "r");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            continue;
        }

        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        if (file_size > MAX_BUFFER_SIZE) {
            fprintf(stderr, "File size exceeds the maximum limit\n");
            fclose(file);
            continue;
        }

        fread(buffer, 1, file_size, file);
        fclose(file);

        printf("Sending %s...\n", filename);
        ssize_t sent_bytes = send(sockfd, buffer, file_size, 0);
        printf("Sent %ld bytes.\n", sent_bytes);
    }

    close(sockfd);
    return 0;
}

