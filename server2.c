#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void ftp_receive_file(int sockfd, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        error("Error opening file");
    }

    char buffer[BUFFER_SIZE];
    ssize_t n;

    while ((n = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, file);
    }

    fclose(file);
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10000);
    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);
    printf("Listening for requests on port 10000\r\n");
    while (1) {
        int newsockfd = accept(sockfd, NULL, NULL);
        char buffer[1024];
        bzero(buffer, sizeof(buffer));
        int n = read(newsockfd, buffer, sizeof(buffer));
        printf("Request:\r\n%s", buffer);
        char response[256];
        if (strncmp(buffer, "GET / ", 6) == 0) {
        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Hello</h1>");
        } else {
        sprintf(response, "HTTP/1.1 404 Not found\r\nContent-Type: text/html\r\n\r\n<h1>Not found</h1>");
        } close(newsockfd);
    } close(sockfd);
    return 0;
}
