//------------------ самостоятельная работа №7 -------------------\\
// необходимо составить алгоритм для простейших арифметических
// опреаций в заданной системе счисления (шестеричной). необходимо
// также реализовать функцию по поиску переполнения во время выполнения
// арифметических опреаций в заданной системе счисления (шестеричной)

#include <stdio.h>

long int step(long int osn, long int pokaz) /*функция по расчёту степени числа*/
{
	long int osn1 = osn;
	long int k = pokaz;
	if (pokaz != 0)
	{
		while (k > 1)
		{
			osn *= osn1;
			k -= 1;
		}
		return osn;
	}
	else
	{
		return 1;
	}
}

long int DecToSix(long int d) /*функция перевода числа из десятичной системы счисления в шестеричную*/
{
	long int i = 1, six = 0;
	while (abs(d) > 0)
	{
		six += d % 6 * i;
		i *= 10;
		d /= 6;
	}
	return six;
}

long int SixToDec(long int s) /*функция перевода числа из шестчеричной системы в десятичную*/
{
	long int k = 0, dec = 0;
	while (abs(s) > 0)
	{
		dec += (s % 10) * step(6, k);
		k += 1;
		s /= 10;
	}
	return dec;
}

long int err(long int a, long int b) /*функция по поиску ошибки переполнения*/
{
	long int constt = 2145555555; /*константа переполнения в шестеричной системе счисления*/
	if (abs(a-b) > abs(SixToDec(constt)))
	{
		return 2; 
	}
	else if (abs(a*a)> abs(SixToDec(constt)))
	{
		return 4;
	}
	else if ((abs(a * a * b) > abs(SixToDec(constt)) || abs(a * (a - b)) > abs(SixToDec(constt))))
	{
		return 3;
	}
	else if (abs(a * a * b - a * (a - b)) > abs(SixToDec(constt)))
	{
		return 2;
	}
	else if (abs(a * a * b - a * (a - b)+a) > abs(SixToDec(constt)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	long int a = 0, b = 0, c = 0; 
	scanf("%ld\n%ld", &a, &b);
	a = SixToDec(a);
	b = SixToDec(b);
	c = step(a, 2) * b - a * (a - b) + a;
	c = DecToSix(c);
	if (err(a, b) == 0)
	{
		printf("%ld\n", c);
	}
	else
	{
		printf("!%ld\n", err(a, b));
	}
}