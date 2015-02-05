#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("PATH=%s\n", getenv("PATH"));
	return 0;
}
