#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	struct hostent * h;
	int i;
	uint32_t addr_int;
	char addr[50];
	char *s;
	while ((h = gethostent()) != NULL) {
		printf("host name: %s\n", h->h_name);
		printf("aliases: \n");
		for (i = 0; h->h_aliases[i]; ++i){
			printf("%s\n", h->h_aliases[i]);
		}

		printf("address: \n");
		for (i = 0; h->h_addr_list[i]; ++i){
			s = inet_ntop(h->h_addrtype, h->h_addr_list[i], addr, 100);
			if (s) printf("%s\n", addr);
		}
		
		printf("\n");
	}
	endhostent();
	return 0;
}
