#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main() {
    // create socket and receive the file descriptor in sockfd
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed to create UDP socket for sender\n");
        return -1;
    }

    // initialize destination address
    sockaddr_in server_addr{};
    int addr_len = sizeof(sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.139"); // my private IP address // convert from string to network representation
    server_addr.sin_port = htons(12345); // run this server on the port: 12345 on all interfaces

    // Send message asynchronously, do not wait for server to be ready, do not wait for answer.
    char message[] = "Some Message";
    size_t message_len = strlen(message) +1; // also send \0
    long long result = sendto(sockfd, message, message_len, 0, (sockaddr*) &server_addr, addr_len);
    if(result < 0){
        printf("Sending not successful\n");
        return -1;
    }

    close(sockfd);

    return 0;
}
