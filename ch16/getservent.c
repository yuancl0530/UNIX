#include <netdb.h>
#include <stdio.h>

int main()
{
	struct servent *s;
	int i;
	while ((s=getservent()) != NULL) {
		printf("name: %s\t",s->s_name);
		printf("aliases names:");
		for (i = 0;s->s_aliases[i];++i)
			printf("%s\t", s->s_aliases[i]);
		printf("\tport: %d\n",s->s_port);
	}
	return 0;
}
