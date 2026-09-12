//------------------ лабораторная работа №12 -------------------\\
// Составить программу, которая содержит две функции, выполняющие сортировку по
// невозрастанию для массива, заполненного целыми числами:
//     1) методом вставки (включения),
//     2) методом обмена («пузырька»).
// Подсчитать количество присваиваний и количество сравнений для каждого метода
// сортировки.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int counter1 = 0; /*глобальные переменные-счётчики количества присваиваний и сравнений соответственно*/
int counter2 = 0;

void full(int* s, int k) /*фцнкция заполнения массива с клавиатуры*/
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


void metod_vstavki(int *s, int l) /*функция сортировки методом вставки*/
{
	for (int i = 1; i<l; i++)
	{
		int c = 0, m = s[i];
		counter1 += 1;
		while (c < i)
		{
			counter2 += 1;
			if (s[c] >= m )
			{
				c += 1;
			}
			else{break;}
		}
		for (int k = i; k>c; k--)
		{
			s[k] = s[k-1];
			counter1 += 1;
		}
		s[c] = m;
		counter1 += 1;
		output(s, l);
		if (i == l-1){printf("\n");}
		else{printf("\n\n");}
	}
}


void metod_obmena(int *s, int l) /*функция сортировки "пузырьковым методом"*/
{
	int m = 0;
	for (int j = 0; j < l-1; j++)
	{
		for (int i = 0; i < l-1-j; i++)
		{
			counter2 += 1;
			if (s[i]<s[i+1])
			{
				m = s[i];
				s[i] = s[i+1];
				s[i+1] = m;
				counter1 += 3;
				
			}
		}
		output(s, l);
		if (j == l-2){printf("\n");}
		else{printf("\n\n");}
	}
}


int main()
{
	int *s1, *s2, l1, a, b; /*объявление массива, его длины, переменных-границ для последнего задания*/

	//printf("введите длину массива: ");
	scanf("%d", &l1);

	s1 = (int*)malloc(l1 * sizeof(int)); /*выделение памяти под динамические массивы*/
	s2 = (int*)malloc(l1 * sizeof(int)); 
	if (s1 == NULL || s2 == NULL) {exit(EXIT_FAILURE);} /*проверка на возможность выделения памяти*/

	full(s1, l1); /*заполнение массива с клавиатуры*/
	for (int i = 0; i<l1; i++) {s2[i] = s1[i];} /*создание копии исходного массива*/

	output(s1, l1);
	printf("\n\n");
	metod_vstavki(s1, l1); /*реализация 1 метода*/
	printf("%d %d\n", counter1, counter2);
	printf("\n");

	counter1 = 0; /*обнуление глобальных переменных для 2 метода*/
	counter2 = 0;

	metod_obmena(s2, l1); /*реализация 2 метода*/
	printf("%d %d\n", counter1, counter2);

	free(s1);
	free(s2);
}