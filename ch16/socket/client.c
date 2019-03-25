#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFSIZE 128

int main()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port=htons(1500);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	bzero(&(addr.sin_zero),8);
	int sockfd;
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		printf("create socket error!\n");
		exit(0);
	}
	if (connect(sockfd,(struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1) {
		printf("connect error: %s\n", strerror(errno));
		exit(0);
	}
	else printf("success to connect!\n");
	char buf[BUFSIZE];
	scanf("%s",buf);
	send(sockfd, buf, strlen(buf)+1,0);
	recv(sockfd, buf, BUFSIZE,0);
	printf("%s\n", buf);
	close(sockfd);
	return 0;
}
