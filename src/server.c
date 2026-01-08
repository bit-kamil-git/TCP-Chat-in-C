#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char **argv) {
    
    if(argc != 2) {
        printf("Usage: ./server <port>\n");
        return 1;
    }

    char *endptr = NULL;
    errno = 0;

    long port_long = strtol(argv[1], &endptr, 10);

    if((endptr == argv[1]) || (*endptr != '\0') || (errno == ERANGE) || (port_long < 1 || port_long > 65535)) {
        fprintf(stderr, "Invalid port\n");
        return 1;
    };

    printf("%ld\n", port_long);

    int port = (int)port_long;

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(listen_fd == -1) {
        perror("socket");
        return 1;
    } else {
        printf("Socket created: %d \n", listen_fd);
    }

    int reuse = 1;

    int ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    if (ret == 0) {
        printf("Success\n");
    } else {
        perror("setsockopt");
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));  // Zero addr before setting fields

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);


    ret = bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));

    if (ret == -1) {
        perror("bind");
        close(listen_fd);
        return 1;
    }

    printf("Bound to port %d\n", port);

    ret = listen(listen_fd, 10);

    if (ret == -1) {
        perror("listen");
        close(listen_fd);
        return 1;
    }

    printf("Listening on port %d \n", port);

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    memset(&client_addr, 0, sizeof(client_addr));


    printf("Waiting for a client...\n");

    int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("accept");
        close(listen_fd);
        return 1;
    }

    char ip_str[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str)) == NULL) {
        perror("inet_ntop");
        close(client_fd);
        close(listen_fd);
        return 1;
    }

    int client_port = ntohs(client_addr.sin_port);
    printf("Client connected from %s:%d (fd=%d)\n", ip_str, client_port, client_fd);

    close(client_fd);
    close(listen_fd);
    return 0;

}
