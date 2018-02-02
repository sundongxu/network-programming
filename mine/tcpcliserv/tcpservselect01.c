#include <unp.h>

int main(int argc, char **argv)
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    maxfd = listenfd;
    maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;)
    {
        rset = allset;
        printf("调用Select之前...\n");
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        printf("调用Select之后...nready=%d\n", nready);

        if (FD_ISSET(listenfd, &rset))
        {
            // 新连接到来
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);

            printf("新连接到来,connfd=%d\n", connfd);

            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE)
                err_quit("too many clients");

            FD_SET(connfd, &allset);
            if (connfd > maxfd)
                maxfd = connfd;
            if (i > maxi)
                maxi = i;
            if (--nready <= 0)
                continue;
        }

        for (i = 0; i <= maxi; i++)
        {
            printf("进入读数据循环...\n");
            if ((sockfd = client[i]) < 0)
            {
                printf("sockfd=%d\n", sockfd);
                continue; // 跳过中间已关闭的fd(client对应位置为-1)
            }
            printf("sockfd>0, sockfd=%d\n", sockfd);
            if (FD_ISSET(sockfd, &rset))
            {
                printf("准备读数据！\n");
                if ((n = Read(sockfd, buf, MAXLINE)) == 0)
                {
                    // 客户关闭连接
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                    printf("server关闭连接...\n");
                }
                else
                {
                    printf("Read被调用！读到%d个字节\n", n);
                    printf("%s\n", buf);
                    Writen(sockfd, buf, n);
                }
                if (--nready <= 0)
                {
                    printf("跳出读数据循环...\n");
                    break;
                }
            }
        }
    }
}