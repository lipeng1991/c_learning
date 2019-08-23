#include <stdio.h>
#include "lib/common.h"
#include "socket/socket_tcp.h"




int main() {
    printf("Hello, World!\n");
    tcp_server_demo();
    client_tcp_demo();
    return 0;
}