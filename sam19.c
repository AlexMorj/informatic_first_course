#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
} Node;

typedef Node *pNode;


void incert (pNode *p, int val) /*функция вставки элемента в дерево*/
{
	if (*p == NULL)
	{
		*p = (Node *) malloc(sizeof(Node));
		(*p)->key = val;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
	else
	{
		if (val < (*p)->key) {incert(&( (*p)->left ), val);}
		else {incert(&( (*p)->right ), val);}
	}
}


void in_order (pNode p) /*функция вывода дерева на экран в форме последовательности,
полученной при симметричном порядке (in-order) обхода всех его узлов*/
{
	if (p != NULL)
	{
		in_order(p->left);
		printf("%3d", p->key);
		in_order(p->right);
	}
}


void post_order (pNode p) /*функция вывода дерева на экран в форме последовательности,
полученной при обратном порядке (post-order) обхода всех его узлов*/
{
	if (p != NULL)
	{	
		post_order(p->left);
		post_order(p->right);
		printf("%3d", p->key);
	}
}


void count_lvl (pNode p, int counter, int *levels) /*функция определения количества уровней
дерева (не считая корня)*/
{
	if (p == NULL) {return;}
	if (counter > *levels) {*levels = counter;}
	count_lvl(p->left, counter+1, levels);
	count_lvl(p->right, counter+1, levels);
}


int sum_one_leaf (pNode p) /*функция расчета суммы значений узлов дерева, имеющего
ровно по одному дочернему узлу*/
{
	int sum = 0;
	if (p == NULL) {return 0;}
	if ((p->left != NULL && p->right == NULL) ||
		(p->left == NULL && p->right != NULL))
	{
		sum += p->key;
	}
	return sum + sum_one_leaf(p->left) + sum_one_leaf(p->right);
}


void print_current_level (pNode p, int level) /*вспомогательная функция вывода
одного уровня дерева*/
{
	if (p == NULL) {return;}
	if (level == 0) {printf("%3d", p->key);}
	else
	{
		print_current_level(p->left, level-1);
		print_current_level(p->right, level-1);
	}
}


void breadth_first (pNode p) /*функция вывода всех уровней дерева*/
{
	int levels = -1;
	count_lvl(p, 0, &levels);
	for (int i = 0; i < levels; i++)
	{
		print_current_level(p, i);
	}
}


void add_rand (pNode *p, int n, int a, int b) /*функция добавления в дерево
случайных чисел из промежутка, вводимого пользователем*/
{
    for (int i = 0; i < n; i++)
	{
		int val = a + rand()%(b-a+1);
		incert(p, val);
	}
}


void clear_tree (pNode *p) /*функция удаления всего дерева*/
{
	if (*p != NULL)
	{
		clear_tree(&((*p)->left));
		clear_tree(&((*p)->right));
		free(*p);
		*p = NULL;
	}
}


pNode search(pNode p, int  val) /*функция поиска заданного значения*/
{
	while (p!= NULL)
	{
		if (val == p->key) {return p;}
		if (val < p->key) {p = p->left;}
		else if (val > p->key) {p = p->right;}
	}
	return NULL;
}


int delete_node(pNode *root, int val) /*функция удаления элемента по значению*/
{
	if (*root == NULL) {return 0;}
	if (search(*root, val) == NULL) {return 0;}
	pNode p = *root;
	pNode par = NULL;
	while (p->key != val)
	{
		par = p;
		if (val < p->key) {p = p->left;}
		else if (val > p->key) {p = p->right;}
	}
	/*случай 1 из методички*/
	if ((p->left == NULL || p->right == NULL) || (p->left == NULL && p->right == NULL))
	{
		pNode child = (p->left != NULL) ? p->left: p->right;
		if (par == NULL) {*root = child;}
		else if (par->left == p) {par->left = child;}
		else if (par->right == p) {par->right = child;}
		free(p);
	}
	else
	{
		pNode spar = p;
		pNode s = p->right;
		while (s->left != NULL)
		{
			spar = s;
			s = s->left;
		}
		p->key = s->key;
		if (spar == p) {spar->right = s->right;}
		else {spar->left = s->right;}
		free(s);
	}
	return 1;
}


void delete_otr(pNode *root, int a, int b) /*функция удаления элементов, принаддежащих диапазону*/
{
	if (*root == NULL) {return;}
	delete_otr(&((*root)->right), a, b);
	delete_otr(&((*root)->left), a, b);
	if (((*root)->right) >= a && ((*root)->right) <= b)
	{
		delete_node(root, (*root)->key);
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

	int del_val;
	if (scanf("%d", &del_val) == 1)
	{
		post_order(root);
		printf("\n");
		int if_deleted = delete_node(&root, del_val);
		if (if_deleted == 0)
		{
			printf("!\n");
			post_order(root);
			printf("\n");
		}
		else
		{
			post_order(root);
			printf("\n");
		}
		printf("%d\n", sum_one_leaf(root));
	}
	clear_tree(&root);
}