#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int counter1 = 0; /*глобальные переменные-счётчики количества присваиваний и сравнений соответственно*/
int counter2 = 0;

void full(int* s, int k) /*функция заполнения массива с клавиатуры*/
{
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &s[i]);
    }
}

void output(int* s, int k) /*функция вывода массива*/
{
    for (int i = 1; i <= k; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
    
    for (int i = 0; i < k; i++)
    {
        printf("%3d", s[i]);
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

void quick_sort(int* s, int l1, int first, int last)
{
    /* Защита от выхода за границы массива (в том числе для l1 = 0) */
    if (first >= last) return; 

    int pivot, l, r;
    l = first; r = last;
    pivot = s[(l + r) / 2]; /*определение опорного значения*/
    counter1 += 1;
    
    while (l <= r)
    {
        /* Заменяем логическое && на явное прерывание для надежного инкремента счетчиков */
        while (1) {
            counter2++;
            if (s[l] <= pivot) break; /* Сортировка по невозрастанию */
            l++;
        }
        while (1) {
            counter2++;
            if (s[r] >= pivot) break;
            r--;
        }
        
        if (l <= r)
        {
            swap(&s[l], &s[r]); /*перестановка двух элементов*/
            if (l != r)
            {
                printf("\n\n");
                output(s, l1);
            }
            l++;
            r--;
        }
    } /*Рекурсивная сортировка:*/
    if (first < r) { quick_sort(s, l1, first, r); } /*- левого участка, */
    if (l < last) { quick_sort(s, l1, l, last); }
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
            if (s[j] > s[j + 1]) {j++;} /*сравнение с меньшим элементом*/
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
    if (l1 <= 1) return;

    int k = l1 / 2, i;
    for (i = k - 1; i >= 0; i--)
    {
        tree_rebuild(s, l1, i, l1 - 1); /*построение пирамиды (только один раз)*/
    }

    for (i = l1 - 1; i >= 1; i--)
    {
        swap(&s[0], &s[i]); /*перестановка 0-го и i-го элементов*/
        
        /* Выводим массив ВСЕГДА после перестановки (даже для i==1) */
        printf("\n\n");
        output(s, l1);
        
        int mirror_counter = counter1;
        tree_rebuild(s, l1, 0, i - 1); /* «проталкивание» i-го элемента*/
        
        if (counter1 > mirror_counter + 2)
        {
            printf("\n\n");
            output(s, l1);
        }
    }
}

int main()
{
    int* s1, * s2, l1;
    
    if (scanf("%d", &l1) != 1) return 0;
    
    /* Обработка случая пустого массива во избежание ошибки malloc(0) */
    if (l1 <= 0) {return 0;}

    s1 = (int*)malloc(l1 * sizeof(int)); /*выделение памяти под динамические массивы*/
    s2 = (int*)malloc(l1 * sizeof(int));
    if (s1 == NULL || s2 == NULL) { exit(EXIT_FAILURE); } /*проверка на возможность выделения памяти*/

    full(s1, l1); /*заполнение массива с клавиатуры*/
    for (int i = 0; i < l1; i++) { s2[i] = s1[i]; } /*создание копии исходного массива*/

    output(s1, l1);

    quick_sort(s1, l1, 0, l1 - 1);
    printf("\n%d %d", counter1, counter2);

    counter1 = 0; /*обнуление глобальных переменных для 2 метода*/
    counter2 = 0;

    tree_sort(s2, l1);
    printf("\n%d %d\n", counter1, counter2);

    free(s1);
    free(s2);
    
    return 0;
}