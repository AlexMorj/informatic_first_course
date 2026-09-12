//------------------ самостоятельная работа №8 -------------------\\
// необходимо реализовать рекурсивную функцию для поиска заданного числа
// последовательности Люка. реализовать алгоритм, позволяющий трассировать
// рекурсионную функцию


#include <stdio.h>
#include <locale.h>
#include <limits.h>
long long int err_overflow = 0; /*глобальная переменная кода ошибки переполнения*/

long long int func(int n, int counter, long long int a, long long int b, int depth) /*рекурсивная функция расчёта заданного
																			числа последовательности Люка. данная функция
																			также выводит таблицу трассировки рекурсии
																			(необходимо раскомментировать строку)*/

{
	if (n == 1) return 1;
	if (n == 2) return 3;
	//if (a > LLONG_MAX - b)
	if (a > LONG_MAX - b)
	{
		err_overflow = 1;
		return 0;
	}
	if (counter > n)
	{
		return b;
	}

	/*УБРАТЬ КОММЕНТАРИЙ С СЛЕДУЮЩЕЙ СТРОКИ ДЛЯ ПЕЧАТИ ТАБЛИЦЫ ТРАССИРОВКИ*/

	//printf("%7d%22lld %lld%27lld\n", depth - 1, a, b, a + b);
	
	long long int result = func(n, counter + 1, b, a + b, depth + 1);
	return result;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	scanf("%d", &n); /*ввод аргументов функции с клавиатуры.*/

	/*УБРАТЬ КОММЕНТАРИЙ С СЛЕДУЮЩЕЙ СТРОКИ ДЛЯ ПЕЧАТИ ТАБЛИЦЫ ТРАССИРОВКИ*/

	//printf("глубина рекурсии    ввод(рекурсивный спуск)    вывод(рекурсивный возврат)\n");

	long long int result = func(n, 3, 1, 3, 1); /*вызов рекурсивной функции*/
	if (err_overflow == 1 || n < 1)
	{
		printf("!\n");
	}
	else
	{
		printf("%lld\n", result);
	}
}