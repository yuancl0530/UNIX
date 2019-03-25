#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 128
int main()
{
	struct sockaddr_in addr;
	int sockfd;
	if ((sockfd=socket(AF_INET, SOCK_STREAM,0) ) ==-1 ){
		printf("create socket error!\n");
		exit(0);
	}
	printf("%d\n",sockfd);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1500);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	bzero(&(addr.sin_zero),8);	
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0) {
		printf("bind error! %s\n", strerror(errno));
		exit(0);
	}
	listen(sockfd, 10);
	char buf[BUFSIZE];
	int len;
	while (1) {
		int fd = accept(sockfd, NULL, &len);
		recv(fd, buf, BUFSIZE, 0);
		printf("%s\n",buf);
		sprintf(buf,"ok");
		send(fd, buf, (ssize_t)strlen(buf)+1,0);
	}
	close(sockfd);
	return 0;
}
