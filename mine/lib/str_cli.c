#include <unp.h>

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    // get bytes from keyboard and store in sendline buffer
    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Writen(sockfd, sendline, strlen(sendline)); // write bytes into socket

        if (Readline(sockfd, recvline, MAXLINE) == 0) // read bytes from socket
            err_quit("str_cli:server terminated prematurely");

        // display on screen
        Fputs(recvline, stdout);
    }
}