//------------------ лабораторная работа №8 -------------------\\
// необходимо реализовать рекурсивную функцию для подсчёта заданной
// функции. реализовать алгоритмы, отслеживающие переполнение
// типа данных unsigned long int во время вычислений и проваливание
// рекурсивной функции в бесконечность


#include <stdio.h>
#include <math.h>
#include <limits.h>
long long int counter = 0; /*глобальная переменная глубины рекурсии*/
long long int err_endless = 0; /*глобальная переменная кода ошибки "зацикливания"*/
long long int err_overflow = 0; /*глобальная переменная кода ошибки переполнения*/

long long int minimum(long long int a, long long int b) /*функция по нахождению минимального из пары чисел*/
{
	if (a <= b)
	{
		return a;
	}
	if (b <= a)
	{
		return b;
	}
}


long long int over(long long int a, long long int b) /*функция, проверяющая переполнение типа данных unsigned long int
														при операции пложении*/
{
	if (a > ULONG_MAX - a)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


long long int func(long long int n, long long int m) /*рекурсивная функция по расчёту значения искомой функции*/
{
	counter += 1; /*увеличение счётчика глубины рекурсии*/
	if (over(n, m) == 1) /*проверка на переполнение при сложении аргументов функции*/
	{
		err_overflow = 1; /*глобальная переменная кода ошибки переполнения получает значение 1*/
		return 0; /*выход из рекурсивной функции*/
	}

	if (counter >= 1000) /*проверка на бесконечность*/
	{
		err_endless = 1; /*глобальная переменная кода ошибки "зацикливания" получает значение 1*/
		return 0; /*выход из рекурсивной функции*/
	}

	else if ((n + m) % 2 != 0) /*проверка четности, необходимая по условию*/
	{
		return minimum(n, m);
	}
	
	else
	{
		long long int func1 = func((n + m) / 2, m); /*рекурсивный вызов функции*/
		if (err_endless == 1 || err_overflow == 1) /*проверка на наличие ошибок*/
		{
			return 0; /*выход из рекурсивной функции*/
		}

		long long int func2 = func(n, (n + m) / 2); /*рекурсивный вызов функции*/
		if (err_endless == 1 || err_overflow == 1) /*проверка на наличие ошибок*/
		{
			return 0; /*выход из рекурсивной функции*/
		}

		if (over(func1, func2) == 1) /*проверка на переполнение*/
		{
			return 0; /*выход из рекурсивной функции*/
		}
		return func1 + func2;
	}
}


int main()
{
	long long int a, b;
	scanf("%lld\n%lld", &a, &b); /*ввод аргументов функции с клавиатуры*/
	long long int result = func(a, b); /*вызов рекурсивной функции*/

	if (err_endless == 1)
	{
		printf("endless\n");
	}
	else if (err_overflow == 1)         /*вывод с учетом возможных ошибок*/
	{
		printf("overflow\n");
	}
	else
	{
		printf("%lld\n", result);
	}
}