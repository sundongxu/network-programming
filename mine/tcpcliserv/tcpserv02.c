#include <unp.h>

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    void sig_chld(int); // declare

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&cliaddr, sizeof(cliaddr));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    Signal(SIGCHLD, sig_chld);

    for (;;)
    {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
        // echo in child process
        if ((childpid = fork()) == 0)
        {
            // child process
            Close(listenfd);  // child close listening fd
            str_echo(connfd); // process requests
            exit(0);          // terminate child process, close all fds opened in child process
        }
        Close(connfd); // parent close fd
    }
}