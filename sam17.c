#include <stdio.h>
#include <stdlib.h>


typedef struct elem
{
	int inf;
	struct elem* link;
} Elem;


// 1. Добавление элемента в начало списка
void push_front(Elem** head, int val)
{
	Elem* p = (Elem*)malloc(sizeof(Elem));
	if (p == NULL) { exit(EXIT_FAILURE); }

	p->inf = val;
	p->link = *head;
	*head = p;
}


// 2. Добавление элемента в конец списка
void push_back(Elem** head, int val)
{
	Elem* p = (Elem*)malloc(sizeof(Elem));
	if (p == NULL) { exit(EXIT_FAILURE); }

	p->inf = val;
	p->link = NULL;

	if (*head == NULL) { *head = p; }
	else
	{
		Elem* temp = *head;
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = p;
	}
}


// 3. Удаление элемента из начала списка
void pop_front(Elem** head)
{
	if (*head == NULL) { return; }
	Elem* p = *head;
	*head = p->link;
	free(p);
}


// 4. Удаление элемента из конца списка
void pop_back(Elem** head)
{
	if (*head == NULL) { return; }
	if ((*head)->link == NULL)
	{
		free(*head);
		*head = NULL;
		return;
	}

	Elem* p = *head;
	while (p->link->link != NULL)
	{
		p = p->link;
	}

	free(p->link);
	p->link = NULL;
}


// 5. Вывод всех элементов списка
void print_list(Elem* head)
{
	Elem* p = head;
	while (p != NULL)
	{
		printf("%4d", p->inf);
		p = p->link;
	}
	printf("\n");
}


// 6. Поиск элемента с заданным значением (возвращает адрес)
Elem* search(Elem* head, int val)
{
	Elem* p = head;
	while (p != NULL)
	{
		if (p->inf == val)
		{
			return p;
		}
		p = p->link;
	}
	return NULL;
}


// 7. Удаление элемента, адрес которого известен
void delete_by_address(Elem** head, Elem* target)
{
	if (*head == NULL || target == NULL) { return; }
	if (*head == target)
	{
		*head = target->link;
		free(target);
		return;
	}

	Elem* p = *head;
	while (p->link != NULL && p->link != target)
	{
		p = p->link;
	}

	if (p->link == target)
	{
		p->link = target->link;
		free(target);
	}
}


int main() {
	Elem* head = NULL;
	int val;

	while (scanf("%d", &val) == 1)
	{
		push_back(&head, val);
	}


	char skip_n;
	scanf(" %c", &skip_n);

	int search_val;
	if (scanf("%d", &search_val) == 1)
	{
		Elem* target = search(head, search_val);
		if (target != NULL)
		{
			delete_by_address(&head, target);
		}
	}
	print_list(head);


	while (head != NULL) {
		pop_front(&head);
	}
}