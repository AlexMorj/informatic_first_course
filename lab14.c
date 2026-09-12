#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


void full(int *s, int k) /*фцнкция заполнения массива с клавиатуры*/
{
	//printf("введите элементы заполняемого массива: ");
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &s[i]);
	}
}


void output(int* s, int k) /*функция вывода массива*/
{
	for (int i = 1; i <= k; i++)
	{
		printf("%3d", i);
	}
	printf("\n");
	for (int i = 0; i < k; i++)
	{
		printf("%3d", s[i]);
	}
}

void outputu(int** s, int k) /*функция вывода массива*/
{
	for (int i = 1; i <= k; i++)
	{
		printf("%3d", i);
	}
	printf("\n");
	for (int i = 0; i < k; i++)
	{
		printf("%3d", *s[i]);
	}
}


int main()
{
	int *s1, *s2, **s0, *se, l1, l2, l0, a, minn = 100000, *m, c;

	setlocale(LC_ALL, "Rus");

	//printf("введите длину массива 1: ");
	scanf("%d", &l1);
	s1 = (int*)malloc(l1 * sizeof(int)); /*выделение памяти под динамические массивы*/
	if (s1 == NULL) { exit(EXIT_FAILURE); } /*проверка на возможность выделения памяти*/
	full(s1, l1);

	//printf("введите длину массива 2: ");
	scanf("%d", &l2);
	s2 = (int*)malloc(l1 * sizeof(int));
	if (s2 == NULL) { exit(EXIT_FAILURE); } /*проверка на возможность выделения памяти*/
	full(s2, l2);


	output(s1, l1);
	printf("\n\n");
	output(s2, l2);
	printf("\n\n");

	l0 = l1 + l2;
	s0 = (int**)malloc(l0 * sizeof(int*));
	if (s0 == NULL) { exit(EXIT_FAILURE); } /*проверка на возможность выделения памяти*/
	

	int i;
	for (i = 0; i < l2; i++)
	{
		s0[i] = &s2[i];
	}
	for (i; i < l0; i++)
	{
		s0[i] = &s1[i - l2];
	}


	for (int i = l2; i < l0; i++)
	{
		c = 0;
		while (*s0[i] > *s0[c])
		{
			c += 1;
		}
		m = s0[i];
		for (int j = i - 1; j >= c; j--)
		{
			s0[j + 1] = s0[j];
		}
		s0[c] = m;
	}


	for (int i = 0; i < l0/2; i++)
	{
		m = s0[i];
		s0[i] = s0[l0 - i - 1];
		s0[l0 - i - 1] = m;
	}


	outputu(s0, l0);
	printf("\n\n");

	free(s1);
	free(s2);
}