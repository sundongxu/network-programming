#include <unp.h>

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE]; // 4096

again:
    while ((n = read(sockfd, buf, n) > 0))
        Writen(sockfd, buf, n);
    if (n > 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");
}