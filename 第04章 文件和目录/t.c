#include <stdio.h>

int main()
{
    char buf[128];
    int n = readlink("./a.link", buf, 128);
    write(1, buf, n);
    return 0;
}
