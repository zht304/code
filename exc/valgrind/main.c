#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
	
	char *p;
	p = malloc(12);

	if(p)
	perror("main");
	return 0;
}
