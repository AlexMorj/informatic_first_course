#include <stdio.h>
int main()
{
	int a, b;
	scanf("%d\n%d", &a, &b);
	int d = a/10+48, e = b/10+48, c = 2*a*b;
	while (c >= 10){
		c/=10;
	}
	int f = c+48;
	printf("%d:%5o%5d%5x\n", d-48, d, d, d);
	printf("%d:%5o%5d%5x\n", e-48, e, e, e);
	printf("%d:%5o%5d%5x\n", c, f, f, f);
}
