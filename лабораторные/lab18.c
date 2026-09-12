#include <stdio.h>
#include <stdlib.h>

typedef struct elem
{
	int inf;
	struct elem* prev;
	struct elem* next;
}Elem;


void push_front(Elem** begl, Elem**endl, int val) /*добавление элемента в начало списка*/
{
	Elem* p = (Elem*)malloc(sizeof(Elem));
	if (p == NULL) { exit(EXIT_FAILURE); }

	p->inf = val;
	p->next = *begl;
	p->prev = NULL;
	if ((*begl) != NULL)
	{
		(*begl)->prev = p;
	}
	else
	{
		(*endl) = p;
	}
	*begl = p;
}


void push_back(Elem** begl, Elem** endl, int val) /*добавление элемента в конец списка*/
{
	Elem* p = (Elem*)malloc(sizeof(Elem));
	if (p == NULL) { exit(EXIT_FAILURE); }

	p->inf = val;
	p->next = NULL;
	p->prev = (*endl);
	if ((*endl) != NULL)
	{
		(*endl)->next = p;
	}
	else
	{
		(*begl) = p;
	}
	(*endl) = p;
}


void dell_front(Elem** begl, Elem** endl) /*удалние элемента из начала списка*/
{
	if (*begl == NULL) { return; }
	Elem* p = *begl;
	*begl = p->next;
	if ((*begl) != NULL)
	{
		(*begl)->prev = NULL;
	}
	else
	{
		*endl = NULL;
	}
	free(p);
}


void dell_back(Elem** begl, Elem** endl) /*удалние элемента из конца списка*/
{
	if (*endl == NULL) { return; }
	Elem* p = *endl;
	*endl = p->prev;
	if ((*endl) != NULL)
	{
		(*endl)->next = NULL;
	}
	else
	{
		*begl = NULL;
	}
	free(p);
}


void print_front(Elem* begl) /*вывод всех элементов списка (нач->кон)*/
{
	Elem* p = begl;
	while (p != NULL)
	{
		printf("%4d", p->inf);
		p = p->next;
	}
	printf("\n");
}


void print_back(Elem* endl) /*вывод всех элементов списка (кон->нач)*/
{
	Elem* p = endl;
	while (p != NULL)
	{
		printf("%4d", p->inf);
		p = p->prev;
	}
	printf("\n");
}


int summa(Elem* begl) /*расчет суммы элементов списка*/
{
	int summ = 0;
	Elem* p = begl;
	while (p != NULL)
	{
		summ += p->inf;
		p = p->next;
	}
	return summ;
}


void dell_all(Elem **begl, Elem **endl) /*очистка списка*/
{
	Elem* p = *begl;
	while (p != NULL)
	{
		Elem *temp = p;
		p = p->next;
		free(temp);
	}
	*begl = NULL;
	*endl = NULL;
}


void add_curent(Elem** begl, Elem** endl, int a, int b, int n, int F) /*добавление в начало/конец списка элементов*/
{
	for (int i = 0; i < n; i++)
	{
		int val = a + rand() % (b - a + 1);
		if (F == 1) {push_back(begl, endl, val);}
		else { push_front(begl, endl, val);}
	}
}


int main()
{
	Elem* Begl = NULL;
	Elem* Endl = NULL;
	int value;

	while (scanf("%d", &value) == 1)
	{
		push_back(&Begl, &Endl, value);
	}
	char n_skip;
	scanf(" %c", &n_skip);

	dell_back(&Begl, &Endl);
	dell_back(&Begl, &Endl);

	print_front(Begl);
	int summ = summa(Begl);
	printf("%d\n", summ);
	dell_all(&Begl, &Endl);
}