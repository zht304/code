#include <stdio.h>

int factorial(int);

int main(int argc, char *argv[])
{
	int n = 1;
	printf("input an intergarte to caculate the factorial of N\n");

	if(argc > 1)
		n = atoi(argv[1]);
	else
		scanf("%d",&n);

	printf("factorial of %d = %d\n", n, factorial(n));
	return 0;
}
