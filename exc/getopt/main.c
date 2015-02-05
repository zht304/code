#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char* argv[], char *env[])
{
	char c;
	while( (c = getopt(argc, argv, "ab:c::") )!= -1)
	{
		switch(c)
		{
			case 'a':
				if(optarg)
					printf("a: optarg=%s, optind=%d\n",
							optarg, optind);
				else
					printf("a: optarg=%x, optind=%d\n",
							optarg, optind);
				break;
			case 'b':
				printf("b: optarg=%s, optind=%d\n",
						optarg, optind);
				break;
			case 'c':
				if(optarg)
					printf("c: optarg=%s, optind=%d\n",
							optarg, optind);
				else
					printf("c: optarg=%x, optind=%d\n",
							optarg, optind);
				break;
			case '?':
				printf("?: optarg=%x, optind=%d\n",
						optarg, optind);
				break;
			default:
				printf("*: optarg=%x, optind=%d\n",
						optarg, optind);
				break;
		}
	}
	printf(" optarg=%x, optind=%d\n",
			optarg, optind);
	return 0;
}
