#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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


    return 0;
}
