#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

static void help(FILE *stream, int err)
{
	fprintf(stream, "aaa --help\n");
	exit(err);
}

int main(int argc, char *argv[], char *env[])
{
	int c;
	const char *outfilename;
	const struct option opt[] = 
	{
		{"help",	0,	NULL,	'h'},
		{"output",	1,	NULL,	'o'},
		{"version",	0,	NULL,	'v'},
		{NULL,		0,	NULL,	0	}
	};
	
	do
	{
		c = getopt_long(argc, argv, "ho:v", opt, NULL);

		switch(c)
		{
			case 'h':
				help(stdout, 0);
				break;
			case 'o':
				outfilename = optarg;
				execl("/bin/cat","cat", optarg/*outfilename*/, NULL);
				break;
			case 'v':
				printf("version 1.0\n");
				break;
			case ':':
				break;
			case '?':
				help(stderr, -1);
				break;
			case -1:
				break;
			default:
				help(stderr, -1);
				break;
		}
	}while(c != -1);

	return 0;
}
