//------------------ самостоятельная работа №13 -------------------\\
// необходимо проанализировать различие в количестве сравнений и 
// присваиваний для двух методов сортировки: обычного метода вставки и
// пирамидального метода. проследить, соотвествует ли теории сложность
// данных алгоритмов.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int counter1 = 0;
int counter2 = 0;

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


void output(int* s, int k) /*функция вывода массива "в строчку"*/
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


void output_ind(int *s, int l) /*функция вывода массива таблицей*/
{
    for (int i = 1; i <= l; i++) {
        printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < l; i++) {
        printf("%3d", s[i]);
    }

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
	//output 2
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
	//output 2
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
	// output 2
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
	// output 2
}


void vstavka(int *s, int l) /*сортировка вставками (по убыванию) */
{
    for (int i = 1; i < l; i++)
    {
        int m = s[i], c = i - 1;
        counter1 += 1;
    
        while (c >= 0)
        {
            counter2 += 1;
            if (s[c] < m) 
            {
                c -= 1;
            }
            else {break;}
        }
        c += 1;
        
        for (int k = i; k > c; k--)
        {
            s[k] = s[k - 1];
            counter1 += 1;
        }
        s[c] = m;
        counter1 += 1;
    }
}


void swap(int* x, int* y)
{
    int temp; /* temp - вспомогательная переменная */
    temp = *x;
    *x = *y;
    *y = temp;
    counter1 += 3;
}


void tree_rebuild(int* s, int l1, int r, int q)
{
    int v, i, j, pp;
    i = r; /*индекс рассматриваемого элемента*/
    v = s[i]; /*рассматриваемый элемент*/
    counter1 += 1;
    j = 2 * i + 1;/*индекс элемента, с которым проводится сравнение*/
    pp = 0; /*предположение, что не найдено место в пирамиде*/
    while (j <= q && !pp)
    {
        if (j < q)
        {
            counter2 += 1;
            if (s[j] > s[j + 1]){j++;} /*сравнение с меньшим элементом*/
        }
        counter2 += 1;
        if (v <= s[j]) {pp = 1;} /*элемент стоит на своем месте*/
        else
        {
            s[i] = s[j]; /*перестановка элемента*/
            counter1 += 1;
            i = j;
            j = 2 * i + 1; /*прохождение дальше по пирамиде*/
        }
        
    }
    s[i] = v;
    counter1 += 1;
}


void tree_sort(int* s, int l1)
{
    int k = l1 / 2, i;
    for (i = k - 1; i >= 0; i--)
    {
        tree_rebuild(s, l1, i, l1 - 1); /*построение пирамиды (только один раз)*/
    }
    for (i = l1 - 1; i >= 1; i--)
    {
        swap(&s[0], &s[i]); /*перестановка 0-го и i-го элементов*/
        tree_rebuild(s, l1, 0, i - 1); /* «проталкивание» i-го элемента*/
    }
}


void sravnenie(int start, int kolvo)
{
    int *s1, *s2;
    int counter_mod1, counter_mod2;
    int counter_std1, counter_std2;

    printf("Оценка сортировок в наихудшем случае (отсортировано по убыванию)\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Размер(N) | Вставка: Присваивания / Сравнения | Пирамидальная: Присваивания / Сравнения\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = start; i <= kolvo+start; i++)
	{

        s1 = (int*)malloc(i * sizeof(int));
        s2 = (int*)malloc(i * sizeof(int));
        if (s1 == NULL || s2 == NULL) { exit(EXIT_FAILURE); }

        full_rand(s1, i, 0, 999);
        
        for (int j = 0; j < i; j++)
		{ 
            s2[j] = s1[j]; 
        }

        counter1 = 0;
        counter2 = 0;
        vstavka(s1, i);
        counter_mod1 = counter1;
        counter_mod2 = counter2;

        counter1 = 0;
        counter2 = 0;
        tree_sort(s2, i);
        counter_std1 = counter1;
        counter_std2 = counter2;

        // 4. Выводим результат текущей итерации
        printf("%8d | %22d / %9d | %27d / %9d\n", i, counter_mod1, counter_mod2, counter_std1, counter_std2);

        // 5. Очищаем память перед следующим кругом
        free(s1);
        free(s2);
    }
}


/*ВЫВОД: по итогам тестов массивов длины 500->1000, заполняемых случайными числами:

Размер(N) | Стандартная: Присваивания / Сравнения | Усовершенствованная: Присваивания / Сравнения
--------------------------------------------------------------------------------
      100 |                   2678 /      2566 |                  1081 /      1025
      200 |                  10800 /      9693 |                  2348 /      2450
      300 |                  22172 /     23571 |                  3710 /      4008
      400 |                  40338 /     40655 |                  5111 /      5689
      500 |                  61588 /     64654 |                  6529 /      7426
      600 |                  89488 /     92004 |                  8005 /      9244
      700 |                 122180 /    124561 |                  9527 /     11123
      800 |                 158622 /    163369 |                 11010 /     12988
      900 |                 203411 /    203830 |                 12559 /     14915
     1000 |                 255417 /    247074 |                 14059 /     16826
     1100 |                 309788 /    297952 |                 15632 /     18800

если построить графики зависимости количества присваиваний от длины массива, то результаты
сойдутся с теорией: график 1 будет подниматься гораздо выше графика 2 с ростом длины массива,
также, график 1 будет иметь бо'льший угловой коэффицент касательной, нежели график 2 при одинаковых
значениях длины массива. таким образом, можно заявить, что в рассмотренных пределах теоретический
расчёт сходится с практикой.*/


int main()
{
	int flag;
	printf("введите 1, чтобы запустить выполнение функций из работ 9, 11\nвведите 2, чтобы запустить работу функций сортировки и сравнения\n");
	scanf("%d", &flag);

	if (flag == 1)
	{
		int *s1, l1, a, b, F; /*объявление массива, его длины, переменных-границ для последнего задания*/
		printf("============ ДЕМОНСТРАЦИЯ РАБОТЫ ФУНКЦИЙ ИЗ САМОСТОЯТЕЛЬНЫХ 9 И 11 ============\n");
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

	else if (flag == 2)
	{
		printf("============ ДЕМОНСТРАЦИЯ РАБОТЫ ФУНКЦИЙ СОРТИРОВКИ И СРАВНЕНИЯ ============\n");

		int start, kolvo;
    	printf("\n--- СРАВНЕНИЕ АЛГОРИТМОВ ---\n");
    	printf("Введите начальную длину массива (N) и количество шагов увеличения: ");
    	scanf("%d %d", &start, &kolvo);
        sravnenie(start, kolvo);

	}	
}