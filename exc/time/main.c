#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int i = 0;
	time_t t;
	for( i = 0; i < 100000; ++i)
	{
		if(i % 1000 == 0)
		{
			printf("clock()=%d\n", clock());
		}
	}


	printf("time()=%d\n", time(&t));
	printf("t=%d\n", t);
	return 0;
}
