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
            char txt[1024];
            FILE *fptr = fopen("file.txt", "r");
            if (fptr != NULL) fread(txt, 1, sizeof(txt), fptr);
            else sprintf(txt, "<h1>Hello World</h1>");
            fclose(fptr);
            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n%s", strlen(txt), txt);
            n = write(newsockfd, response, strlen(response));
        } else if (strncmp(buffer  "STOR ", 5) == 0) {
            FILE *fptr = fopen("file.txt", "w");
            n = read(newsockfd, buffer, sizeof(buffer));
            fprintf(fptr, "%s", buffer);
            fclose(fptr);
        } else {
            sprintf(response, "HTTP/1.1 404 Not found\r\nContent-Type: text/html\r\n\r\n<h1>Not found</h1>");
            n = write(newsockfd, response, strlen(response));
        } close(newsockfd);
    } close(sockfd);
    return 0;
}
