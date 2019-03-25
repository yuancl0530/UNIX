## stat/fstat/fstatat/lstat
```c
#include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int fd, struct stat * buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
int fstatat(int fd, const char *restrict pathname,struct stat *restrict buf, int flags);
//成功返回0，出错返回-1
```
* stat返回与此命名文件相关的信息结构
* fstat获得已在文件描述符fd上打开的文件有关的信息
* lstat类似于stat，但当命名为一个符号链接时，返回该符号链接有关的信息，而不是所引用文件的信息
* fstatat返回一个相对于当前打开目录的路径的文件统计信息。
	* flags = AT_SYMLINK_NOFOLLOW，不跟随符号链接
### 结构信息
```c
struct stat{
	mode_t             st_mode;   //file type & mode(permissions)
	ino_t              st_ino;    //i-node number (serial number)
	dev_t              st_dev;    //device number (file system)
	dev_t              st_rdev;   //device number for special files
	nlink_t            st_nlink;  //numner of links
	uid_t              st_uid;    //UID
	gid_t              st_gid;    //GID
	off_t              st_size;   //size in bytes, for regular files
	struct timespec    st_atime;  //time of last access
	struct timespec    st_mtime;  //time of last modification
	struct timespec    st_ctime;  //time of last file status change
	blksize_t          st_blksize;//best I/O block size
	blkcnt_t           st_blocks; //number of disk blocks allocated
};
```

## 文件类型
1. 普通文件
2. 目录文件
3. 块特殊文件。提供对设备带缓冲的访问，每次访问长度固定
4. 字符特殊文件。提供对设备不带缓冲的访问，每次访问长度可变
5. FIFO。用于进程间通信
6. 套接字。 用于进程间网络通信
7. 符号链接

文件类型宏
| 宏 | 对象类型 |
|--|--|
| S_ISREG() | 普通文件 |
| S_ISDIR() | 目录文件 |
| S_ISCHR() | 字符特殊文件 |
| S_ISBLK() | 块特殊文件 |
| S_ISFIFO() | 管道或FIFO |
| S_ISLNK() |  符号链接 |
| S_ISSOCK() | 套接字 |

## 文件访问权限
| st_mode屏蔽 | 含义 |
|--|--|
| S_IRUSR | 用户读 |
| S_IWUSR | 用户写 |
| S_IXUSR | 用户执行 |
| S_IRGRP | 组读 |
| S_IWGRP | 组写 |
| S_IXGRP | 组执行 |
| S_IROTH | 其他读 |
| S_IWOTH | 其他写 |
| S_IXOTH | 其他执行 |

## 文件权限测试access/faccessat
```c
#include <unistd.h>
int access(const char *pathname, int mode);
int faccessat(int fd, const char *pathname, int mode, int flag);
// mode： R_OK W_OK X_OK
//成功返回0，失败返回-1
```
* flag=AT_EACCESS访问检查用的是有效用户ID和有效组ID

## umask
umask函数为文件设置文件模式创建屏蔽字
```c
mode_t umask(mode_t cmask);
//返回之前的文件模式创建屏蔽字
```
## chmod/fchmod/fchmodat
```c
#include <sys/stat.h>
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);
//成功返回0，失败返回-1
```
* flags = AT_SYMLINK_NOFOLLOW，不跟随符号链接
* mode

| mode | 说明 |
|---|---|
| S_ISUID  | 执行时设置用户ID |
| S_ISGID  | 执行时设置组ID   |
| S_ISVTX  | 保存正文（粘着位）|
| S_IRWXU  | 用户读写执行 |
| S_IRUSR | 用户读 |
| S_IWUSR | 用户写 |
| S_IXUSR | 用户执行 |
| S_IRWXG | 组读写执行 |
| S_IRGRP | 组读 |
| S_IWGRP | 组写 |
| S_IRWXO | 其他读写执行|
| S_IXGRP | 组执行 |
| S_IROTH | 其他读 |
| S_IWOTH | 其他写 |
| S_IXOTH | 其他执行 |

## chown/fchown/fchownat/;chown
```c
#include <unistd.h>
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag);
int lchown(const char *pathname, uid_t owner, gid_t group);
//成功返回0，失败返回-1
```
## 文件截断
```c
#include <unistd.h>
int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length);
//成功返回0，失败返回-1
```
## 链接
```c
#include <unistd.h>
int link(const char *exitstingpath, const char *newpath);
int linkat(int efd, const char *existingpathm int nfd, const char *newpath, int flag);
//成功返回0，失败返回-1 
```

```c
#include <unistd.h>
int unlink(const char *pathname);
int unlinkat(int fd, const char *pathname, int flag);
//成功返回0，失败返回-1 
```
* flag=AT_REMOVEDIR类似于rmdir
```c
#include <stdio.h>
int remove(const char *pathname);
//成功返回0，失败返回-1 
```

## rename/renameat
```c
#include <stdio.h>
int rename(const char *oldname, const char *newname);
int rename(int oldfd, const char *oldname, int newfd, const char *newname);## stat/fstat/fstatat/lstat
```c
#include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int fd, struct stat * buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
int fstatat(int fd, const char *restrict pathname,struct stat *restrict buf, int flags);
//成功返回0，出错返回-1
```
* stat返回与此命名文件相关的信息结构
* fstat获得已在文件描述符fd上打开的文件有关的信息
* lstat类似于stat，但当命名为一个符号链接时，返回该符号链接有关的信息，而不是所引用文件的信息
* fstatat返回一个相对于当前打开目录的路径的文件统计信息。
	* flags = AT_SYMLINK_NOFOLLOW，不跟随符号链接
### 结构信息
```c
struct stat{
	mode_t             st_mode;   //file type & mode(permissions)
	ino_t              st_ino;    //i-node number (serial number)
	dev_t              st_dev;    //device number (file system)
	dev_t              st_rdev;   //device number for special files
	nlink_t            st_nlink;  //numner of links
	uid_t              st_uid;    //UID
	gid_t              st_gid;    //GID
	off_t              st_size;   //size in bytes, for regular files
	struct timespec    st_atime;  //time of last access
	struct timespec    st_mtime;  //time of last modification
	struct timespec    st_ctime;  //time of last file status change
	blksize_t          st_blksize;//best I/O block size
	blkcnt_t           st_blocks; //number of disk blocks allocated
};
```

## 文件类型
1. 普通文件
2. 目录文件
3. 块特殊文件。提供对设备带缓冲的访问，每次访问长度固定
4. 字符特殊文件。提供对设备不带缓冲的访问，每次访问长度可变
5. FIFO。用于进程间通信
6. 套接字。 用于进程间网络通信
7. 符号链接

文件类型宏
| 宏 | 对象类型 |
|--|--|
| S_ISREG() | 普通文件 |
| S_ISDIR() | 目录文件 |
| S_ISCHR() | 字符特殊文件 |
| S_ISBLK() | 块特殊文件 |
| S_ISFIFO() | 管道或FIFO |
| S_ISLNK() |  符号链接 |
| S_ISSOCK() | 套接字 |

## 文件访问权限
| st_mode屏蔽 | 含义 |
|--|--|
| S_IRUSR | 用户读 |
| S_IWUSR | 用户写 |
| S_IXUSR | 用户执行 |
| S_IRGRP | 组读 |
| S_IWGRP | 组写 |
| S_IXGRP | 组执行 |
| S_IROTH | 其他读 |
| S_IWOTH | 其他写 |
| S_IXOTH | 其他执行 |

## 文件权限测试access/faccessat
```c
#include <unistd.h>
int access(const char *pathname, int mode);
int faccessat(int fd, const char *pathname, int mode, int flag);
// mode： R_OK W_OK X_OK
//成功返回0，失败返回-1
```
* flag=AT_EACCESS访问检查用的是有效用户ID和有效组ID

## umask
umask函数为文件设置文件模式创建屏蔽字
```c
mode_t umask(mode_t cmask);
//返回之前的文件模式创建屏蔽字
```
## chmod/fchmod/fchmodat
```c
#include <sys/stat.h>
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);
//成功返回0，失败返回-1
```
* flags = AT_SYMLINK_NOFOLLOW，不跟随符号链接
* mode

| mode | 说明 |
|---|---|
| S_ISUID  | 执行时设置用户ID |
| S_ISGID  | 执行时设置组ID   |
| S_ISVTX  | 保存正文（粘着位）|
| S_IRWXU  | 用户读写执行 |
| S_IRUSR | 用户读 |
| S_IWUSR | 用户写 |
| S_IXUSR | 用户执行 |
| S_IRWXG | 组读写执行 |
| S_IRGRP | 组读 |
| S_IWGRP | 组写 |
| S_IRWXO | 其他读写执行|
| S_IXGRP | 组执行 |
| S_IROTH | 其他读 |
| S_IWOTH | 其他写 |
| S_IXOTH | 其他执行 |

## chown/fchown/fchownat/;chown
```c
#include <unistd.h>
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag);
int lchown(const char *pathname, uid_t owner, gid_t group);
//成功返回0，失败返回-1
```
## 文件截断
```c
#include <unistd.h>
int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length);
//成功返回0，失败返回-1
```
## 链接
```c
#include <unistd.h>
int link(const char *exitstingpath, const char *newpath);
int linkat(int efd, const char *existingpathm int nfd, const char *newpath, int flag);
//成功返回0，失败返回-1 
```

```c
#include <unistd.h>
int unlink(const char *pathname);
int unlinkat(int fd, const char *pathname, int flag);
//成功返回0，失败返回-1 
```
* flag=AT_REMOVEDIR类似于rmdir
```c
#include <stdio.h>
int remove(const char *pathname);
//成功返回0，失败返回-1 
```

## rename/renameat
```c
#include <stdio.h>
int rename(const char *oldname, const char *newname);
int rename(int oldfd, const char *oldname, int newfd, const char *newname);
//成功返回0，失败返回-1 
```
## 创建符号链接
```c
#include <unistd.h>
int symlink(const char *actualpath, const char *sympath);
int symlinkat(const char *actualpath, int fd, const char *sympath);
//成功返回0，失败返回-1 
```

```c
#include <unistd.h>
ssize_t readlinl(const char *restrict pathname, char *restrict buf, 
		size_t bufsize);
ssize_t readlinkat(int fd, const char *restrict pathname, 
	char *restrict buf, size_t bufsize);
//成功返回字节数，失败返回-1
```
## 文件时间

文件相关的时间字段
| 字段 | 说明 | 例子 | ls 选项|
|--|--|---|----|
| st_atime | 文件数据最后访问的时间 | read | ls -u|
| st_mtime | 文件数据最后修改的时间 | write | default |
| st_ctime | 节点状态最后更改时间 | chmod、chown | -c |

## 修改文件时间
```c
#include <unistd.h>
int futimens(int fd, const struct timespec times[2]);
int utimensat(int fd, const char *path, const struct timespec times[2], int flag);
//成功返回字节数，失败返回-1
```
times第一个元素包含访问时间（st_atime)，第二个元素包含修改时间(st_mtime)
tmies:
1. times参数为NULL，设置为当前时间
2. tv_nsec=UTIME_NOW,当前时间
3. tv_nsec=UTIME_OMIT,保持不变

## mkdir/mkdirat/rmdir
```c
#include <sys/stat.h>
int mkdir(const char *pathname, mode_t mode);
int mkdirat(int fd, const char *pathname, mode_t mode);
int rmdir(const char *pathname);
//成功返回字节数，失败返回-1
```

## 读目录
```c
#include <dirent.h>
DIR *opendir(const char *pathname);
DIR *fdopendir(int fd);
//成功返回指针，失败返回NULL

struct dirent *readdir(DIR *dp);
//成功返回指针，出错或读到目录尾返回NULL

void rewinddir(DIR *dp);
//用来设置参数dir目录流目前的读取位置为原来开头的读取位置，没有返回值的函数。

int closedir(DIR *dp);
//成功返回0，失败返回-1

long telldir(DIR *dp);//返回与dp关联的目录中的当前位置

void seekdir(DIR *dp, long loc);

struct dirent{
	ino_t  d_ino;    //i-node number
	char   d_name[];   //null-terminated filename
};
```

## chdir/fchdir/getcwd
```c
//调用chdir和fdchdir函数可以更改当前工作目录
int chdir(const char *pathname);
int fchdir(int fd);
//若成功返回0， 出错返回-1

char *getcwd(char *buf, size_t size);
```
//成功返回0，失败返回-1 
```
## 创建符号链接
```c
#include <unistd.h>
int symlink(const char *actualpath, const char *sympath);
int symlinkat(const char *actualpath, int fd, const char *sympath);
//成功返回0，失败返回-1 
```

```c
#include <unistd.h>
ssize_t readlinl(const char *restrict pathname, char *restrict buf, 
		size_t bufsize);
ssize_t readlinkat(int fd, const char *restrict pathname, 
	char *restrict buf, size_t bufsize);
//成功返回字节数，失败返回-1
```
## 文件时间

文件相关的时间字段
| 字段 | 说明 | 例子 | ls 选项|
|--|--|---|----|
| st_atime | 文件数据最后访问的时间 | read | ls -u|
| st_mtime | 文件数据最后修改的时间 | write | default |
| st_ctime | 节点状态最后更改时间 | chmod、chown | -c |

## 修改文件时间
```c
#include <unistd.h>
int futimens(int fd, const struct timespec times[2]);
int utimensat(int fd, const char *path, const struct timespec times[2], int flag);
//成功返回字节数，失败返回-1
```
times第一个元素包含访问时间（st_atime)，第二个元素包含修改时间(st_mtime)
tmies:
1. times参数为NULL，设置为当前时间
2. tv_nsec=UTIME_NOW,当前时间
3. tv_nsec=UTIME_OMIT,保持不变

## mkdir/mkdirat/rmdir
```c
#include <sys/stat.h>
int mkdir(const char *pathname, mode_t mode);
int mkdirat(int fd, const char *pathname, mode_t mode);
int rmdir(const char *pathname);
//成功返回字节数，失败返回-1
```

## 读目录
```c
#include <dirent.h>
DIR *opendir(const char *pathname);
DIR *fdopendir(int fd);
//成功返回指针，失败返回NULL

struct dirent *readdir(DIR *dp);
//成功返回指针，出错或读到目录尾返回NULL

void rewinddir(DIR *dp);
//用来设置参数dir目录流目前的读取位置为原来开头的读取位置，没有返回值的函数。

int closedir(DIR *dp);
//成功返回0，失败返回-1

long telldir(DIR *dp);//返回与dp关联的目录中的当前位置

void seekdir(DIR *dp, long loc);

struct dirent{
	ino_t  d_ino;    //i-node number
	char   d_name[];   //null-terminated filename
};
```

## chdir/fchdir/getcwd
```c
//调用chdir和fdchdir函数可以更改当前工作目录
int chdir(const char *pathname);
int fchdir(int fd);
//若成功返回0， 出错返回-1

char *getcwd(char *buf, size_t size);
```