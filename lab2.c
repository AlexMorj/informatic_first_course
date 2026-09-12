												/*лабораторная работа №2*/
#include <stdio.h>

int main() // функция main(), выполняющая все вычисления, необходимые для решения задачи
{
	int a, a1, a2, m, k=1, k1 = 1; // объявление переменных для задания 1 и счетчиков для задания 2
	double ch = 5, ch1 = 5; // объявление чисел, в которые будут записаны результаты возведения 5 в степень
	scanf("%d %d %d", &a, &a1, &a2);
	scanf("%d", &m);

	if (a1 > a && a > a2 || a2 > a && a > a1) // строки 11-59: обработка всех возможных вариантов комбинаций а, а1, а2
	{
		printf("%d\n\n", a);
	}

	else if (a > a1 && a1 > a2 || a2 > a1 && a1 > a)
	{
		printf("%d\n\n", a1);
	}

	else if (a > a2 && a2 > a1 || a1 > a2 && a2 > a)
	{
		printf("%d\n\n", a2);
	}

	else if (a == a1 && a1 > a2)
	{
		printf("%d=%d>%d\n\n", a, a1, a2);
	}

	else if (a == a2 && a > a1)
	{
		printf("%d=%d>%d\n\n", a, a2, a1);
	}

	else if (a1 == a2 && a1 > a)
	{
		printf("%d=%d>%d\n\n", a1, a2, a);
	}

	else if (a == a1 && a1 < a2)
	{
		printf("%d=%d<%d\n\n", a, a1, a2);
	}

	else if (a == a2 && a < a1)
	{
		printf("%d=%d<%d\n\n", a, a2, a1);
	}

	else if (a1 == a2 && a1 < a)
	{
		printf("%d=%d<%d\n\n", a1, a2, a);
	}

	else if (a == a1 && a1 == a2)
	{
		printf("%d=%d=%d\n\n", a, a1, a2);
	}

	while (ch <= m) // возведение числа 5 в степень до тех пор, пока оно не привысит вводимое m
	{
		ch *= 5;
		k += 1;
	}
	printf("%d\n\n", k);
	while (k1 <= 12) // цикл для вывода таблицы значений 5^1 --> 5^12
	{
		printf("%3d  %.0f\n", k1, ch1);
		ch1 *= 5;
		k1 += 1;
	}
}