## 文件描述符
```
STDIN_FILENO 0
STDOUT_FILENO 1
STDERR_FILENO 2
```
## open and openat
```c
#include <fcntl.h>
int open(const char * path, int pflag, .../*mode_t mode*/);
int openat(int fd, const char *path, .../*mode_t mode*/);
//成功返回文件描述符,出错返回-1
```

* path要打开或创建的文件名
* oflag选项:
	* O_RDONLY 只读打开
	* O_WRONLY 只写打开
	* O_RWONLY 读写打开
	* O_EXEC 只执行打开
	* O_REARCH 只搜索打开(目录)
	* 以上只能指定一个
	* O_APPEND 每次写时追加到文件尾端
	* O_CLOSEXEC 把FD_CLOSEXEC设置成文件描述符
	* O_CREAT 文件不存在则创建心文件.要设置mode
	* O_DIRECTORY 如果path不是目录则出错
	* O_EXCL 指定了O_CREAT并且文件已经存在则出错
	* O_NOCTTY 如果path是终端设备,则不将该设备作为此进程的控制终端
	* O_NOFOLLOW path符号链接则出错
	* O_NONBLCOK path为FIFO、块特殊文件、字符特殊文件则出错
	* O_SYNC 使每次write等待物理IO操作完成
	* O_TRUNC 如果文件存在，并且以只写/读写方式打开，则清空文件全部内容。
	* O_DSYNC 等待物理 I/O 结束后再 write。在不影响读取新写入的数据的前提下，不等待文件属性更新。
	* O_RSYNC read 等待所有写入同一区域的写操作完成后再进行。
	* O_SYNC 等待物理 I/O 结束后再 write，包括更新文件属性的 I/O。

## creat
```c
#include <fcntl.h>
int creat(const char *path, mode_t mode);
//成功返回只写打开的文件描述符，否则返回-1
```
等价于`open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);`

## close
```c
#include <unistd.h>
int close(int fd);
//return:success 0, error -1
```
## lseek
设置文件初始偏移量
```c
#include <unistd.h>
off_t lseek(int fd, off_t offset, int where);
```
where:
* SEEK_SET , 偏移量设置为offset个字节
* SEEK_CUR， 当前值+offset
* SEEK_END，文件长度+offset

## read
```c
#incldue <unistd.h>
ssize_t read(int fd, void *buf, size_t nbytes);
//返回值： 读到的字节数， 若已到达文件尾返回0； 出错返回-1
```

## write
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t nbytes);
//返回值： 已写的字节数； 出错返回-1
```

## dup and dup2
```c
#include <unistd.h>
int dup(int fd);
int dup2(int fd, int fd2); //fd2指定新的文件描述符,若fd2文件已打开，则关闭
//成功返回新的文件描述符，出错返回-1
```

## sync fsync fdatasync
```c
#include <unistd.h>
int fsync(int fd);
int fdatasync(int fd);
//成功返回0；出错返回-1
void sync();
```
* sync将所有修改过的块缓冲区排入写队列，不等待写磁盘结束
* fsync 只对文件描述符fd的文件起作用，等待写磁盘结束返回
* fdatasync类似fsync，但是只影响文件数据部分