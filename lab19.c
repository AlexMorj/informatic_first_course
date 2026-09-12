#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
} Node;

typedef Node* pNode;


void incert(pNode* p, int val) /*функция вставки элемента в дерево*/
{
	if (*p == NULL)
	{
		*p = (Node*)malloc(sizeof(Node));
		(*p)->key = val;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
	else
	{
		if (val < (*p)->key) { incert(&((*p)->left), val); }
		else { incert(&((*p)->right), val); }
	}
}


void in_order(pNode p) /*функция вывода дерева на экран в форме последовательности,
полученной при симметричном порядке (in-order) обхода всех его узлов*/
{
	if (p != NULL)
	{
		in_order(p->left);
		printf("%3d", p->key);
		in_order(p->right);
	}
}


void post_order(pNode p) /*функция вывода дерева на экран в форме последовательности,
полученной при обратном порядке (post-order) обхода всех его узлов*/
{
	if (p != NULL)
	{
		post_order(p->left);
		post_order(p->right);
		printf("%3d", p->key);
	}
}


void count_lvl(pNode p, int counter, int* levels) /*функция определения количества уровней
дерева (не считая корня)*/
{
	if (p == NULL) { return; }
	if (counter > *levels) { *levels = counter; }
	count_lvl(p->left, counter + 1, levels);
	count_lvl(p->right, counter + 1, levels);
}


int sum_one_leaf(pNode p) /*функция расчета суммы значений узлов дерева, имеющего
ровно по одному дочернему узлу*/
{
	int sum = 0;
	if (p == NULL) { return 0; }
	if ((p->left != NULL && p->right == NULL) ||
		(p->left == NULL && p->right != NULL))
	{
		sum += p->key;
	}
	return sum + sum_one_leaf(p->left) + sum_one_leaf(p->right);
}


void print_current_level(pNode p, int level) /*вспомогательная функция вывода
одного уровня дерева*/
{
	if (p == NULL) { return; }
	if (level == 0) { printf("%3d", p->key); }
	else
	{
		print_current_level(p->left, level - 1);
		print_current_level(p->right, level - 1);
	}
}


void breadth_first(pNode p) /*функция вывода всех уровней дерева*/
{
	int levels = -1;
	count_lvl(p, 0, &levels);
	for (int i = 0; i <= levels; i++)
	{
		print_current_level(p, i);
	}
}


void add_rand(pNode* p, int n, int a, int b) /*функция добавления в дерево
случайных чисел из промежутка, вводимого пользователем*/
{
	for (int i = 0; i < n; i++)
	{
		int val = a + rand() % (b - a + 1);
		incert(p, val);
	}
}


void clear_tree(pNode* p) /*функция удаления всего дерева*/
{
	if (*p != NULL)
	{
		clear_tree(&((*p)->left));
		clear_tree(&((*p)->right));
		free(*p);
		*p = NULL;
	}
}

int main()
{
	pNode root = NULL;
	int val;
	while (scanf("%d", &val) == 1)
	{
		incert(&root, val);
	}

	char skip_n;
	scanf(" %c", &skip_n);
	post_order(root);
	printf("\n");
	printf("%d\n", sum_one_leaf(root));
	clear_tree(&root);
}