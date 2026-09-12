#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void full (int **a, int n, int m) /*функция заполнения двумерного массива с клавиатуры*/
{
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
}


void full_rand(int **matrix, int n, int m) /*функция заполнения двумерного массива случайными числами из заданного диапазона*/
{
	int stime, value, a, b;
	long int ltime;
	ltime = time(NULL);
	stime = (unsigned)ltime / 2;
	srand(stime);
	printf("введите границы заполняемости массива: ");
	scanf("%d %d", &a, &b);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			value = rand() % (b-a+1) + (a); // заполнение списка случайными символами
			matrix[i][j] = value;
		}
	}
}


void output (int **a, int n, int m) /*функция форматного вывода двумерного массива*/
{
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%6d", a[i][j]);
		}
		printf("\n");
	}
}


int summa(int **a, int **b, int m1, int n1_cur, int m2_cur) /*вспомогательная функция скалярного произведения строки на столбец*/
{
	int summ = 0;
	for (int i = 0; i < m1; i++)
	{
		summ += a[n1_cur][i]*b[i][m2_cur];
	}
	return summ;
}


void write(int **matrix, int n, int m, char* name) /*запись двумерного массива в текстовый файл*/
{
	FILE *file;
	file = fopen(name, "w");
	if (!file) {exit(EXIT_FAILURE);}
    fprintf(file, "%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
        for (int j = 0; j < m; j++)
        {
		    fprintf(file, "%d ", matrix[i][j]);
        }
	}
	printf("запись прошла успешно\n");
	fclose(file);
}


void read(char *name) /*функция чтения из указанного текстового файла двумерного массива типа int. в начале файла на новой
						строке необходимо задать количество строк и столбцов матрицы через пробел*/
{
	FILE *file;
	int **matrix, n, m;
	file = fopen(name, "r");
	if (!file) {exit(EXIT_FAILURE);}
	fscanf(file, "%d", &n);
    fscanf(file, "%d", &m);
    matrix = (int**)malloc(n*sizeof(int*) + n*m*sizeof(int));
    for (int i = 0; i < n; ++i)
	{
        matrix[i] = (int*)(matrix + n) + i*m;
    }

    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

	output(matrix, n, m);
    free(matrix);
	fclose(file);
}


int** transposition(int **matrix, int n, int m)
{
    int **result = (int**)malloc(m * sizeof(int*) + m * n * sizeof(int));
    if (result == NULL) {exit(EXIT_FAILURE);}
    for (int i = 0; i < m; ++i)
	{
        result[i] = (int*)(result + m) + i * n;
    }
    
    for (int i = 0; i < m; i++)
	{
        for (int j = 0; j < n; j++)
		{
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}


int** summa_matrix(int **a, int **b, int n1, int m1, int n2, int m2) /*функция суммирования матриц с проверкой на возможность операции*/
{
	if (n1 != n2 || m1 != m2)
	{
		printf("!1\n");
		return NULL;
	}
	else
	{
		int **matrix = (int**)malloc(n1*sizeof(int*) + m1*n1*sizeof(int));
		if (matrix == NULL) { exit(EXIT_FAILURE); }
		for (int i = 0; i < n1; ++i)
		{
        	matrix[i] = (int*)(matrix + n1) + i*m1;
    	}

		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < m1; j++)
			{
				matrix[i][j] = a[i][j] + b[i][j];
			}
		}
		return matrix;
	}
}


int** product_matrix(int **a, int **b, int n1, int m1, int n2, int m2) /*функция произведения матриц с проверкой на возможность операции*/
{
	if (m1 != n2)
	{
		printf("!2\n");
		return NULL;
	}
	else
	{
		int **matrix = (int**)malloc(n1*sizeof(int*) + m2*n1*sizeof(int));
		if (matrix == NULL) { exit(EXIT_FAILURE); }
		for (int i = 0; i < n1; ++i)
		{
        	matrix[i] = (int*)(matrix + n1) + i*m2;
    	}

		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < m2; j++)
			{
				matrix[i][j] = summa(a, b, m1, i, j);
			}
		}
		return matrix;
	}
}


int** power_matrix(int **a, int n, int m, int p) /*функция возведения матрицы в степень с проверкой на возможность операции*/
{
    if (n != m)
	{
        printf("!3\n");
        return NULL;
    }
    if (p == 0)
	{
        int **identity = (int**)malloc(n * sizeof(int*) + n * n * sizeof(int));
        if (identity == NULL) {exit(EXIT_FAILURE);}
        for (int i = 0; i < n; ++i)
		{
            identity[i] = (int*)(identity + n) + i * n;
		}

        for (int i = 0; i < n; i++)
		{
            for (int j = 0; j < n; j++)
			{
                if (i == j) {identity[i][j] = 1;}
				else {identity[i][j] = 0;}
            }
        }
        return identity;
    }
    int **result = (int**)malloc(n * sizeof(int*) + n * n * sizeof(int));
    if (result == NULL) {exit(EXIT_FAILURE);}
    for (int i = 0; i < n; ++i)
	{
        result[i] = (int*)(result + n) + i * n;
    }

    for (int i = 0; i < n; i++)
	{
        for (int j = 0; j < n; j++)
		{
            result[i][j] = a[i][j];
        }
    }
    for (int i = 1; i < p; i++) {
        int **temp = product_matrix(result, a, n, n, n, n);
        if (temp == NULL)
		{
            free(result);
            return NULL;
        }
        free(result);
        result = temp;
    }
    return result;
}


int main()
{
	int **a, **b, n1, m1, n2, m2;
	int **sum = NULL, **prod1 = NULL, **prod2 = NULL, **pow = NULL, **aT = NULL;

	scanf("%d %d", &n1, &m1);
	a = (int**)malloc(n1*sizeof(int*) + n1*m1*sizeof(int));
	if (a == NULL) { exit(EXIT_FAILURE); }
	for (int i = 0; i < n1; ++i)
	{
        a[i] = (int*)(a + n1) + i*m1;
    }
	full(a, n1, m1);

	scanf("%d %d", &n2, &m2);
	b = (int**)malloc(n2*sizeof(int*) + n2*m2*sizeof(int));
	if (b == NULL) { exit(EXIT_FAILURE); }
    for (int i = 0; i < n2; i++)
    {
        b[i] = (int*)(b + n2) + i*m2;
    }
	full(b, n2, m2);


	aT = transposition(a, n1, m1);
    if (!aT) {goto cleanup;}

    prod1 = product_matrix(a, aT, n1, m1, m1, n1);
    if (!prod1) {goto cleanup;}

    prod2 = product_matrix(a, b, n1, m1, n2, m2);
    if (!prod2) {goto cleanup;}

    if (n1 != m2) {goto cleanup;}
    pow = power_matrix(prod2, n1, m2, 2);
    if (!pow) {goto cleanup;}

    sum = summa_matrix(prod1, pow, n1, n1, n1, n1);
    if (!sum) {goto cleanup;}

    output(sum, n1, n1);

	cleanup:
		free(a);
		free(b);
		free(aT);
		free(prod1);
		free(prod2);
		free(pow);
		free(sum);
}