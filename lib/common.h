//
// Created by 李鹏 on 2019/8/23.
//

#ifndef YOLANDA_COMMON_H
#define YOLANDA_COMMON_H

#include    <sys/types.h>    /* basic system data types */
#include    <sys/socket.h>    /* basic socket definitions */
#include    <sys/time.h>    /* timeval{} for select() */
#include    <time.h>        /* timespec{} for pselect() */
#include    <netinet/in.h>    /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>    /* inet(3) functions */
#include    <errno.h>
#include    <fcntl.h>        /* for nonblocking */
#include    <netdb.h>
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>    /* for S_xxx file mode constants */
#include    <sys/uio.h>        /* for iovec{} and readv/writev */
#include    <unistd.h>
#include    <sys/wait.h>
#include    <sys/un.h>        /* for Unix domain sockets */

# include    <sys/select.h>    /* for convenience */
# include    <sys/sysctl.h>
# include    <poll.h>        /* for convenience */
# include    <strings.h>        /* for convenience */
# include    <sys/ioctl.h>
# include    <pthread.h>
#define    SERV_PORT      9527
#define    MAXLINE        4096
#define    UNIXSTR_PATH   "/var/lib/unixstream.sock"
#define    LISTENQ        1024
#define    BUFFER_SIZE    4096

#endif //YOLANDA_COMMON_H


