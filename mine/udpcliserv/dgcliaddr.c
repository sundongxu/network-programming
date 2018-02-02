#include <unp.h>

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    socklen_t len;
    struct sockaddr *preply_addr;

    preply_addr = Malloc(servlen);

    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        len = servlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len); // 返回数据报发送者的地址结构
        if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0)
        {
            // 数据报并非来自服务器
            printf("reply from %s (ignored)\n", Sock_ntop(preply_addr, len));
            continue;
        }
    }
    recvline[n] = 0; // 最后一位置位\0表示有效内容(strlen返回有效内容长度)终止
    Fputs(recvline, stdout);
}