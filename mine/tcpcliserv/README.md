## 文件内容
---

### TCP Server
---

#### tcpserv01.c 
说明：原始版本回射服务器</br>
客户端：**tcpcli01.c**</br>
编译链接：
> gcc tcpserv01.c ../lib/str_echo.c -o tcpserv01 -lunp

#### tcpserv02.c 
说明：增加SIGCHLD信号处理(wait)，回收僵死进程资源</br>
客户端：**tcpcli01.c**</br>
编译链接：
> gcc tcpserv02.c ../lib/str_echo.c sigchldwait.c -o tcpserv02 -lunp

#### tcpserv03.c
说明：代码、功能同tcpserv02.c</br>
客户端：**tcpcli04.c**</br>
编译链接：
> gcc tcpserv03.c ../lib/str_echo.c sigchldwait.c -o tcpserv03 -lunp

#### tcpser04.c
说明：完善SIGCHLD信号处理(循环调用waitpid)，完全回收僵死进程资源</br>
客户端：**tcpcli04.c**</br>
编译链接：
> gcc tcpserv04.c ../lib/str_echo.c sigchldwaitpid.c -o tcpserv04 -lunp

#### tcpserv08.c 
说明：对接收到的以文本形式传输的两个数求和，运算结果总是正确，与主机字节序无关</br>
客户端：**tcpcli08.c**</br>
编译链接：
> gcc tcpserv08.c str_echo08.c sigchldwaitpid.c -o tcpserv08 -lunp

#### tcpserv09.c
说明：对接收到的以二进制结构形式传输的两个数求和，只有相同主机字节序机器之间进行运算结果才正确</br>
客户端：**tcpcli09.c**</br>
编译链接：
> gcc tcpserv09.c str_echo09.c sigchldwaitpid.c -o tcpserv09 -lunp

#### tcpservselect01.c
说明：利用select同时监听**监听套接字**和**已连接套接字**</br>
客户端：**tcpcli05.c**与**tcpcli06.c**</br>
编译链接：
> gcc tcpservselect01.c -o tcpservselect01 -lunp

#### tcpservpoll01.c
说明：利用poll同时监听**监听套接字**和**已连接套接字**</br>
客户端：**tcpcli05.c**</br>
编译连接：
> gcc tcpservpoll01.c -o tcpservpoll01 -lunp

### TCP Client
---

#### tcpcli01.c 
说明：原始版本回射客户端</br>
编译链接：
> gcc tcpcli01.c ../lib/str_cli.c -o tcpcli01 -lunp

#### tcpcli04.c 
说明：构造5个socket，并创建5个连接，客户关闭时导致在同一时刻有5个**不排队**的SIGCHLD信号递交给父进程</br>
编译链接：
> gcc tcpcli04.c ../lib/str_cli.c -o tcpcli04 -lunp

#### tcpcli05.c
说明：利用select同时监听**标准输入流**和**已连接套接字**</br>
编译链接：
> gcc tcpcli05.c ../select/strcliselect01.c -o tcpcli05-01 -lunp
> gcc tcpcli05.c ../select/strcliselect02.c -o tcpcli05-02 -lunp

#### tcpcli06.c
说明：直接往对端写入字符串"foo"，随后睡眠30s，拒绝服务攻击，阻止其余客户获取服务</br>
编译链接：
> gcc tcpcli06.c ../select/strcliselect02.c -o tcpcli06 -lunp

#### tcpcli08.c
说明：发送两个字符串整数给服务器求和</br>
编译链接：
> gcc tcpcli08.c strcli08.c -o tcpcli08 -lunp

#### tcpcli09.c
说明：发送两个二进制整数给服务器求和</br>
编译链接：
> gcc tcpcli09.c str_cli09.c -o tcpcli09 -lunp

#### tcpcli11.c
说明：产生SIGPIPE信号</br>
编译链接：
> gcc tcpcli11.c str_cli11.c -o tcpcli11 -lunp
