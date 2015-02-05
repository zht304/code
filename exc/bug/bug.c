#include <stdio.h>
#include <stdlib.h>

static char xxx[1024];
static char buf[512];
static char *string;
int main(int argc, char ** argv)
{
	static char dump[50]={1};
//	gets(string);
	gets(buf);
	string = buf;
	puts(string);
	return 0;
}


