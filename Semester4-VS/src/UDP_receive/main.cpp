#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    long long result = -1;
    unsigned BUFFER_SIZE = 20;
    char buffer[BUFFER_SIZE];

    // sockfd is a file descriptor for the newly created socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed to create the UDP socket for receiver\n");
        return -1;
    }

    // Assign Address and Port of own socket
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    // INADDR_ANY: pseudo address representing all local interfaces (there might be more than one for servers)
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); // htons: host to network-short -> conversion of number format
    server_addr.sin_port = htons(12345); // run this server on the port: 12345 on all interfaces

    // Bind socket to own address in order to be able to receive packages with this destination address
    result = bind(sockfd, (sockaddr *) &server_addr, sizeof(sockaddr_in));
    if (result < 0) {
        return -1;
    }

    // Address of client unknown so far, but will be filled when receiving a message
    sockaddr_in client_addr{};
    int addr_len = sizeof(sockaddr_in);

    // block and wait until message arrives
    result = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (sockaddr *) &client_addr, (socklen_t *) &addr_len);
    if(result < 0){
        perror("Receiving not successful\n");
        return -1;
    }

    // convert IP address of sender to format
    const int ADDRESS_SIZE = 20;
    char address[ADDRESS_SIZE];
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, address, ADDRESS_SIZE);

    printf("Received: \"%s\" (%lld bytes) from address: '%s'", buffer, result, address);

    close(sockfd);

    return 0;
}
