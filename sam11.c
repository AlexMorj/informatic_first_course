//------------------ самостоятельная работа №11-------------------\\
// Необходимо переработать функции самостоятельной работы №9 для оперирования
// с динамическими массивами, реализовать следующие функции:
// 2.1) Сохранение массива в текстовый файл.
// 2.2) Чтение массива из текстового файла.
// 2.3) Удаление нескольких элементов из указанного места (со сдвигом).
// 2.4) Добавление нескольких элементов в указанное место (со сдвигом).
// 3.0) Изменение порядка расстановки элементов массива по определённому правилу
// 4.0) Удаление из массива элементов, лежащих в указанном отрезке

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void null(int *s, int k) /*функция обнуления массива*/
{
	for (int i = 0; i < k; i++)
	{
		s[i] = 0;
	}
}


void full(int* s, int k) /*фцнкция заполнения массива с клавиатуры*/
{
    for (int i = 0; i < k; i++)
	{
        scanf("%d", &s[i]);
    }
}


void full_rand(int *s, int k, int a, int b) /*функция заполнения массива случайными числами из заданного диапазона*/
{
	int stime, value;
	long int ltime;
	ltime = time(NULL);
	stime = (unsigned)ltime / 2;
	srand(stime);

	for (int i = 0; i < k; i++)
	{
		value = rand() % (b-a+1) + (a); // заполнение списка случайными символами
		s[i] = value;
	}
}


void output(int* s, int k) /*функция вывода массива*/
{
	for (int i = 0; i < k; i++)
	{
		if (i == 0)
		{
			printf("%d", s[i]);
		}
		else
		{
			printf(" %d", s[i]);
		}
	}
	printf("\n");
}


int mass_summa(int* s, int k) /*функция расчёта суммы элементов массива*/
{
	int summ = 0;
	for (int i = 0; i < k; i++)
	{
		summ += s[i];
	}
	return summ;
}


double mass_srz(int* s, int a, int b)  /*функция расчёта среднего арифметического элементов массива из заданного диапазона*/
{
    int summ = 0, c = 0;
    for (int i = a - 1; i < b; i++, c++) {
        summ += s[i];
    }
    if (c == 0) return 0;
    return (double)summ / c;
}


void write(int *s, int l, char* name) /*запись массива в текстовый файл*/
{
	FILE *file;
	file = fopen(name, "w");
	if (!file) {exit(EXIT_FAILURE);}
	for (int i = 0; i < l; i++)
	{
		fprintf(file, "%d ", s[i]);
	}
	fclose(file);
}


void read(int **s, int *l, char *name) /*функция чтения из указанного текстового файла массива типа int неизвестной длины и запись полученного в динамический массив*/
{
	FILE *file;
	int c = 0, *q, value;
	file = fopen(name, "r");
	if (!file) {exit(EXIT_FAILURE);}

	*s = (int*)malloc(1*sizeof(int));
	if (*s == NULL) { exit(EXIT_FAILURE); }

	while (fscanf(file, "%d", &value) == 1)
	{
		(*s)[c] = value;
		c += 1;
		q = (int*)realloc(*s, (1+c)*sizeof(int));
		if(q==NULL){exit(EXIT_FAILURE);}
		*s = q;
	}

	if (c > 0)
	{
        int *q = (int*)realloc(*s, c * sizeof(int));
        if (q != NULL) { *s = q; }
    }
	else
	{
        // Если файл был пустой
        free(*s);
        *s = NULL;
    }

    *l = c;
    fclose(file);
}


void dellete(int **s, int *l, int n, int k) /*функция удаления из массива указанного числа элементов, начиная с известного порядкового номера*/
{
	int *q;

	for (int i = n+k-1; i<*l; i++)
	{
		(*s)[i-k] = (*s)[i];
	}
	q = (int*)realloc(*s, (*l-k)*sizeof(int));
	if (q == NULL) { exit(EXIT_FAILURE); }
	*l -= k;
	*s = q;
}


void appendd(int **s, int *l, int n, int k, int *new_elems) /*функция добавления в массив указанного числа элементов, начиная с известного порядкового номера*/
{
    int *q = (int*)realloc(*s, (*l + k) * sizeof(int));
    if (q == NULL) { exit(EXIT_FAILURE); }
    *s = q;

    for (int i = *l - 1; i >= n - 1; i--)
	{
        (*s)[i + k] = (*s)[i];
    }
    
    for (int i = 0; i < k; i++) 
	{
        (*s)[n - 1 + i] = new_elems[i];
    }

    *l += k;
}


void change(int *s, int l, int n) /*функция замены последних 2n элементов массива*/
{
	if (2 * n > l) return;
	int h, m = l-1;
	for (int j = 1; j <= n; j++)
	{
		h = s[m-2*n+j];
		s[m-2*n+j] = s[m-n+j];
		s[m-n+j] = h;
	}
	for (int j = 1; j<=n/2; j++)
	{
		h = s[m-n+j];
		s[m-n+j] = s[l-j];
		s[l-j] = h;
	}
}


void removve(int **s, int *l, int a, int b) /*функция удаления из массива элементов, находящихся в заданном отрезке (последнее задание самостоятельной)*/
{
	int c = 0, *q;
	for (int i = 0; i < *l; i++)
	{
    	if ((*s)[i] < a || (*s)[i] > b)
		{
        	(*s)[c] = (*s)[i];
			c += 1;
		}
	}

	if (c == 0)
	{
        free(*s);
        *s = NULL;
		*l = 0;
    } 
	else
	{
		q =(int*)realloc(*s, c*sizeof(int)); /*нет проверки на нулевой адрес памяти, тк происходит уменьшение выделяемой памяти*/
		*s = q;
		*l = c;
	}
}


int main()
{
	int *s1, l1, a, b, F; /*объявление массива, его длины, переменных-границ для последнего задания*/
	
	printf("введите длину массива: ");
	scanf("%d", &l1);

	s1 = (int*) malloc(l1*sizeof(int)); /*выделение памяти под динамический массив*/
	if(s1==NULL){exit(EXIT_FAILURE);}


	printf("введите 1, чтобы заполнить массив вручную\nвведите 2, чтобы заполнить массив автоматически\n");
	scanf("%d", &F);
	if (F == 2)
	{
		printf("введите границы заполняемости массива (a b): ");
		scanf("%d %d", &a, &b);
		full_rand(s1, l1, a, b);
		printf("\nсгенерированный массив:\n");
	}
	else if (F == 1)
	{
		printf("введите массив вручную\n");
		full(s1, l1);
		printf("\nзаполненный массив:\n");
	}
    output(s1, l1);

    // 2. Расчеты
    printf("сумма элементов: %d\n", mass_summa(s1, l1));
    
    int in1, in2;
    printf("сведите порядковые номера элементов (от и до) для расчёта среднего значения: ");
    scanf("%d %d", &in1, &in2);
    printf("среднее арифметическое: %f\n", mass_srz(s1, in1, in2));

    // 3. Файловые операции
    char *name = "example.txt";
    write(s1, l1, name);
    printf("\nмассив сохранен в файл '%s'.\n", name);

    printf("Чтение массива из файла...\n");
    read(&s1, &l1, name);
    printf("Считанный массив: ");
    output(s1, l1);

    // 4. Удаление элементов
    int n, k;
    printf("\nвведите порядковый номер элемента, с которого удалить, и количество: ");
    scanf("%d %d", &n, &k);
    dellete(&s1, &l1, n, k);
    printf("массив после удаления: ");
    output(s1, l1);

    // 5. Добавление элементов
    printf("\nвведите порядковый номер элемента, с которого добавить, и количество: ");
    scanf("%d %d", &n, &k);
    
    int *new_elems = (int*)malloc(k * sizeof(int));
    printf("введите %d новых элементов: ", k);
    for(int i = 0; i < k; i++) 
	{
        scanf("%d", &new_elems[i]);
    }
    
    appendd(&s1, &l1, n, k, new_elems);
    free(new_elems);
    printf("массив после добавления: ");
    output(s1, l1);
	printf("\nитоговая длина массива: %d", l1);
	printf("\n");

    // 6. Перестановка (задание 3)
    int swap_n;
    printf("\nвведите число 'n' для перестановки последних 2n элементов (2n <= длины массива): ");
    scanf("%d", &swap_n);
    change(s1, l1, swap_n);
    printf("массив после перестановки: ");
    output(s1, l1);

    // 7. Удаление элементов в отрезке (задание 4)
    printf("\nвведите отрезок значений [a, b] для удаления элементов: ");
    scanf("%d %d", &a, &b);
    removve(&s1, &l1, a, b);
    printf("массив после очистки отрезка [%d; %d]: ", a, b);
    if (s1 != NULL && l1 > 0) {
        output(s1, l1);
    } else {
        printf("массив пуст.\n");
    }

	free(s1);
}