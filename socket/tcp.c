//
// Created by 李鹏 on 2019/8/23.
//

#include "../lib/common.h"

#define MESSAGE_SIZE 102400
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 12345

void send_data(int sockfd){
    char *query;
    //初始化一个长度为MESSAGE_SIZE长度的字符串流
    query = malloc(MESSAGE_SIZE +1);
    for (int i = 0; i < MESSAGE_SIZE; i++)
    {
        query[i] = 'a';
        /* code */
    }
    query[MESSAGE_SIZE] = '\0';

    const char *cp;
    cp = query;
    size_t remaining = strlen(query);
    while (remaining)
    {
        // 调用send函数将MESSAGE_SIZE长度的字符串流发送出去
        int n_written = send(sockfd,cp,remaining,0);
        fprintf(stdout, "send into buffer %d \n", n_written);
        if (n_written <=0)
        {
            perror("send");
            return;
        }
        remaining -= n_written;
        cp += n_written;

        /* code */
    }


}

int client_tcp_demo()
{
    int sockfd;
    struct sockaddr_in servaddr;

    // 创建socket套接字，调用connect向对应服务器发起连接请求
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &servaddr.sin_addr);
    int connect_rt = connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr));
    if (connect_rt < 0)
    {
        perror("connect failed");
    }
    //调用send_data 发送数据
    send_data(sockfd);
    exit(0);
}

/* 从 socketfd 描述字中读取 "size" 个字节. */
size_t readn(int fd, void *buffer, size_t size) {
    /*
    在没有读满size个字节之前，一直要循环下去
    非阻塞I/O的情况下，没有数据可以读，需要继续调用read
    */
    char *buffer_pointer = buffer;
    int length = size;
    // 每次让应用程序都读到size个字节
    while (length > 0) {
        // READ函数要求操作系统内核从套接字socketfd读取多少个字节(size),并将
        // 结果存储到buffer中。返回值告诉我们实际读取的字节数目，也有一些特殊情况，如果返回值为0
        // 表示EOF(end-of-file),这在网络中表示对端发送了FIN包，要处断连情况；
        // 如果返回值为-1，表示出错。
        int result = read(fd, buffer_pointer, length);

        if (result < 0) {
            if (errno == EINTR)
                continue;     /* 考虑非阻塞的情况，这里需要再次调用 read */
            else
                return (-1);
        } else if (result == 0) //读到对方发送FIN包，表现形式是EOF此时需要关闭套接字
            break;                /* EOF(End of File) 表示套接字关闭 */
        //需要读的字符数减少，缓存缓存指针往下移动
        length -= result;
        buffer_pointer += result;
    }
    // 读取到EOF跳出循环后，返回实际读取的字符数
    return (size - length);        /* 返回的是实际读取的字节数 */
}

void read_data(int sockfd)
{
    ssize_t  n;
    char buf[1024];

    int time = 0;
    for ( ; ; ) {
        /*实际每次读取1K数据，之后休眠1秒，用来模拟服务器端处理延迟
        */
        fprintf(stdout, "block in read\n");
        if ( (n = readn(sockfd, buf, 1024)) == 0)
            return;

        time ++;
        fprintf(stdout, "1K read for %d \n", time);
        usleep(1000);
    }
}


void tcp_server_demo(){
    /*
    创建socket套接字，bind到对应地址和端口，并开始调用listen接口基监听
    */
    int                 listenfd, connfd;
    socklen_t           clilen;
    struct sockaddr_in  cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(12345);

    /* bind 到本地地址，端口为 12345 */
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    /* listen 的 backlog 为 1024 */
    listen(listenfd, 1024);

    /* 循环处理用户请求 */
    for ( ; ; ) {
        /* 循环等待连接，通过accept获取实际的连接套接字，并开始读取数据
        */
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        read_data(connfd);   /* 读取数据 */
        close(connfd);          /* 关闭连接套接字，注意不是监听套接字 */
    }
}


