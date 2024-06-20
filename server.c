#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

enum Constants {
    PORT_NUM = 0000,
    MAX_SIZE = 10240,
    MID_SIZE = 1024,
    MIN_SIZE = 256,
};

void error(char *msg) {

    fprintf(
        stderr,
        "\nError: %s\n",
        msg
    );

    exit(0);

}

int main() {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("Unable to create socket");

    int optval = 1;

    setsockopt(
        sockfd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &optval,
        sizeof(optval)
    );

    struct sockaddr_in serv_addr;

    bzero(
        (char *)&serv_addr,
        sizeof(serv_addr)
    );

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT_NUM);

    int binding = bind(
        sockfd,
        (struct sockaddr*)&serv_addr,
        sizeof(serv_addr)
    );

    if (binding < 0)
        error("Unable to bind socket");

    listen(sockfd, 1);

    while (1) {

        int newsockfd = accept(
            sockfd,
            NULL,
            NULL
        );

        if (newsockfd < 0)
            error("Unable to accept connection");

        char buffer[MIN_SIZE];

        bzero(
            buffer,
            sizeof(buffer)
        );

        int n = read(
            newsockfd,
            buffer, 
            sizeof(buffer) - 1
        );

        if (n < 0) 
            error("Unable to read requests");

        buffer[n] = '\0';

        printf(
            "Requests: \n%s\n",
            buffer
        );

        #include "control.c"
        handleRequests(buffer);

        close(newsockfd);

    }

    close(sockfd);

    exit(0);

}
