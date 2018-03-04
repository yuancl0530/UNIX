#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#define N 100
int main()
{
	char buf[N];
	pid_t pid;
	int status;

	printf("%%");
	while (fgets(buf,N,stdin)){
		if (buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = 0;
		if ((pid = fork()) < 0){//fork创建子进程，父进程返回子进程的ID，子进程返回0.调用一次，返回两次
			fprintf(stderr,"fork error\n");
			exit(-1);
		}
		else if (pid == 0){
			execlp(buf,buf,(char *)0);
			printf("error\n");
			exit(127);
		}

		if ((pid=waitpid(pid,&status,0)) < 0){
			fprintf(stderr,"waitpid error\n");
			exit(-1);
		}
		printf("%%");
	}
	return 0;
}
