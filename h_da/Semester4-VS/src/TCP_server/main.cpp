#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

void send_message(int sockfd, int count);

int main() {

    int sockfd;

    // SOCK_STREAM indicates TCP
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Server: ERROR: cannot create TCP socket");
        return -1;
    }

    // set own address and bind to socket
    sockaddr_in server_addr{};
    bzero((char *) &server_addr, sizeof(server_addr)); // clear the data structure server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // all ip addresses this device has
    server_addr.sin_port = htons(12345); // htons: host to network short: conversion of number formats

    if (bind(sockfd, (sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Server: ERROR: cannot bind local address to socket");
        return -1;
    }

    // wait for connection requests
    // 5 connection requests are queued, further will be refused
    listen(sockfd, 5); // mark this socket as a passive socket (a socket to listen on)

    int count = 0;
    while (1) {

        sockaddr_in client_addr{};
        int client_addr_len = sizeof client_addr;
        // block until a request arrives
        // a new socket will be returned. The initial socket is only a listener and can be reused
        int new_sockfd = accept(sockfd, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);

        if (new_sockfd < 0) {
            perror("Server: ERROR: failed to accept connection request");
            return -1;
        }

        // let new process handle the request and get back to further requests
        ++count; // increment counter before the processes memory segment is copied
        int child_pid;
        if ((child_pid = fork()) < 0) {
            perror("Server: ERROR: failed to fork");
            return -1;
        } else if (child_pid == 0) {
            close(sockfd); // close the copy of the parents passive socket
            send_message(new_sockfd, count);
            return 0;
        }

        close(new_sockfd); // only child works with this socket
    }
}

void send_message(int sockfd, int count) {
    char message[] = "This is the first message from server to client";
    const int SIZE = (int) strlen(message) + 1; // also send string terminator '\0'
    send(sockfd, message, SIZE, 0);

    char message2[] = "This is the second message";
    const int SIZE2 = (int) strlen(message2) + 1; // also send string terminator '\0'
    send(sockfd, message2, SIZE2, 0);

    printf("%i clients served\n", count);
    close(sockfd);
}
