#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem /*структура для хранения "коллизионных" элементов
					таблицы в виде односвязного списка*/
{
	char name[20];
	struct elem* link;
}Elem;

typedef Elem* pElem;

pElem* create_hesh(int m) /*функция создания хеш-таблицы*/
{
	pElem* table = (pElem*)malloc(m * sizeof(pElem));
	if (table == NULL) { exit(EXIT_FAILURE); }
	for (int i = 0; i < m; i++)
	{
		table[i] = NULL;
	}
	return table;
}

int hash_function(char* name, int m) /*функция реализации хеш-функции*/
{
	int h = 0;
	for (int i = 0; name[i] != '\0'; i++)
	{
		h += (unsigned char)name[i];
	}
	return h % m;
}


void incert_in_hesh(pElem* table, int m, char* name) /*функция добавления элемента в таблицу*/
{
	int indx = hash_function(name, m);
	pElem new_node = (pElem)malloc(sizeof(Elem));
	if (new_node == NULL) { exit(EXIT_FAILURE); }
	strcpy(new_node->name, name);
	new_node->link = table[indx]; /*а в самое его начало, чтобы сократить время на переборе списка*/
	table[indx] = new_node;
}


int search(pElem* table, char* target, int m, int* counter) /*функция поиска элемента таблицы*/
{
	pElem p = table[hash_function(target, m)];
	while (p != NULL)
	{
		(*counter) += 1;
		if (strcmp(p->name, target) == 0) { return 1; }
		p = p->link;
	}
	return 0;
}


int max_len_of_elem(pElem* table, int m) /*функция подстчета количества элементов
										   в самой длинной цепочке*/
{
	int max = 0;
	for (int i = 0; i < m; i++)
	{
		pElem p = table[i];
		int current = 0;
		while (p != NULL)
		{
			current += 1;
			p = p->link;
		}
		if (current > max) { max = current; }
	}
	return max;
}


float fill_factor(int n, int m) /*коэффицент заполнения таблицы*/
{
	return (float)n / m;
}


void free_table(pElem* table, int m) /*безопасная очистка таблицы*/
{
	for (int i = 0; i < m; i++)
	{
		pElem p = table[i];
		while (p != NULL)
		{
			pElem temp = p;
			p = p->link;
			free(temp);
		}
	}
	free(table);
}


int main()
{
	int m = 13;
	int n = 10;
	int counter = 0;
	char name[20];
	char target[20];
	pElem* table = create_hesh(m);

	for (int i = 0; i < n; i++)
	{
		scanf("%s", name);
		incert_in_hesh(table, m, name);
	}
	scanf("%s", target);

	if (search(table, target, m, &counter)) {
		printf("%s\n", target);
	}
	else {
		printf("not found\n");
	}
	printf("%d\n", max_len_of_elem(table, m));
	printf("%.2f\n", fill_factor(n, m));

	free_table(table, m);
	return 0;
}
