#include <unp.h>

int main(int argc, char **argv)
{
    int i, sockfd[5];
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: tcpcli <IPAddress>");

    for (i = 0; i < 5; i++)
    {
        sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        Connect(sockfd[i], (SA *)&servaddr, sizeof(servaddr));
    }

    str_cli(stdin, sockfd[0]); // write bytes from standard input to socket

    exit(0);
}