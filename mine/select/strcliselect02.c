#include <unp.h>

void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1, stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    for (;;)
    {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(sockfd, fileno(fp)) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset))
        {
            if ((n = Read(sockfd, buf, MAXLINE)) == 0)
            {
                if (stdineof == 1) // 客户正常终止：客户先终止标准输入，再遇到socket的EOF条件(对端进程终止关闭链连接发来FIN)
                    return;
                else
                    err_quit("str_cli: server terminated prematurely"); // 客户异常终止：服务器先终止，客户读到EOF
            }
            Write(fileno(stdout), buf, n);
        }

        if (FD_ISSET(fileno(fp), &rset))
        {
            if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) // ctrl+D产生一个EOF
            {
                stdineof = 1;              // 标准输入流此后不会再有输入
                Shutdown(sockfd, SHUT_WR); // 关闭写端，发送FIN
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}