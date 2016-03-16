//
// Created by thomas on 16/03/16.
//

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

int main() {
    int listenfd,connfd;
    int numRead;
    struct sockaddr_in servaddr;
    char buff[4096];
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket error");
        exit(1);
    }
    // Define the characterics of the potential client and the port
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8080);

    // Bind to the port
    if (bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr))) {
        perror("bind error");
        exit(1);
    }

    // Listen to a possible connnection to the given port
    if (listen(listenfd, 1024) < 0) {
        perror("listen");
        exit(1);
    }

    // Answer the connection
    for (;;) {
        // Accept the connection
        if ((connfd = accept(listenfd, (struct sockaddr*) NULL, NULL)) < 0) {
            perror("accept errror");
            exit(1);
        }
        while ((numRead = read(connfd,buff,4096)) > 0){
            if (write(STDOUT_FILENO, buff, numRead) != numRead) {
                perror("write error");
                exit(1);
            }
        }

        // Close the connection
        close(connfd);
    }
}