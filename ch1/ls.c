#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>  //UNIX类目路操作头文件

/*

*/

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;
	if (argc !=2 ){
		fprintf(stderr,"usage:ls directory_name\n");
		exit(1);
	}
	dp = opendir(argv[1]);
	if (!dp){
		fprintf(stderr,"can't open %s\n",argv[1]);
		exit(1);
	}
	while (dirp=readdir(dp))
		printf("%s\n",dirp->d_name);
	closedir(dp);
	return 0;
}
