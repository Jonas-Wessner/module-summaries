#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main() {

    int sockfd;

    // SOCK_STREAM indicates TCP
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client: ERROR: cannot create TCP socket");
        return -1;
    }

    // set server address
    sockaddr_in server_addr{};
    bzero((char *) &server_addr, sizeof(server_addr)); // clear the data structure server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.139"); // my private ip address
    server_addr.sin_port = htons(12345); // htons: host to network short: conversion of number formats

    if (connect(sockfd, (sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Client: ERROR: cannot connect socket to server");
        return -1;
    }

    const int SIZE = 100;
    char buffer[SIZE];
    if (recv(sockfd, buffer, SIZE, 0) < 0) {
        perror("Client: ERROR: failure to receive message");
        return -1;
    }
    close(sockfd);

    printf("Client received: \"%s\"", buffer);
    // Client may print both messages, one, or only parts,
    // depending on when the packages are sent and when recv is called
    // Order is guaranteed, but how many packets get delivered and when is unknown

    return 0;
}
