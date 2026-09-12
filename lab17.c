#include <stdio.h>
#include <stdlib.h>

typedef struct elem
{
	int f;
	struct elem* link;
}Elem;


void push(Elem** top, int val)
{
	Elem* p = (Elem*)malloc(sizeof(Elem));
	if (p == NULL) { exit(EXIT_FAILURE); }

	p->link = *top;
	p->f = val;
	*top = p;
}


void dell(Elem** top)
{
	if (*top == NULL) { return; }
	Elem* p = *top;
	*top = p->link;
	free(p);
}


void print(Elem* top)
{
	Elem* p = top;
	while (p != NULL)
	{
		printf("%4d", p->f);
		p = p->link;
	}
	printf("\n");
}


int summ(Elem* top)
{
	int summ = 0;
	Elem* p = top;
	while (p != NULL)
	{
		summ += p->f;
		p = p->link;
	}
	return summ;
}


void push_cur(Elem** top, int n, int a, int b)
{
	for (int i = 0; i < n; i++)
	{
		int val = a + rand() % (b - a + 1);
		push(top, val);
	}
}

void dell_all(Elem** top)
{
	while (*top != NULL)
	{
		dell(top);
	}
}


int main()
{
	Elem* Top = NULL;
	int value;

	while (scanf("%d", &value) == 1)
	{
		push(&Top, value);
	}

	for (int i = 0; i < 2; i++)
	{
		dell(&Top);
	}
	
	print(Top);
	
	int summa = summ(Top);
	printf("%d\n", summa);
	dell_all(&Top);
}