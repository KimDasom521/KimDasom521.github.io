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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char filename[MAX_FILENAME_LENGTH];
    char buffer[MAX_BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    printf("Server listening on port %d...\n", portno);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    while (1) {
        bzero(filename, MAX_FILENAME_LENGTH);

        ssize_t received_bytes = recv(newsockfd, filename, MAX_FILENAME_LENGTH - 1, 0);
        if (received_bytes <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        filename[received_bytes] = '\0';

        if (strcmp(filename, "quit") == 0) {
            printf("Exiting...\n");
            break;
        }

        printf("File Name: %s\n", filename);

        ssize_t received_file_size = recv(newsockfd, buffer, MAX_BUFFER_SIZE, 0);
        printf("Received %ld bytes.\n", received_file_size);

        char new_filename[MAX_FILENAME_LENGTH + 6]; // "_copy" suffix
        snprintf(new_filename, sizeof(new_filename), "%s_copy", filename);

        FILE *file = fopen(new_filename, "w");
        if (!file) {
            fprintf(stderr, "Error creating file: %s\n", new_filename);
            break;
        }

        fwrite(buffer, 1, received_file_size, file);
        fclose(file);
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}
