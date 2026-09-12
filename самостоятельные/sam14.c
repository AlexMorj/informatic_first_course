#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_len 50
#define max_str 250


void output(char **s, int k) /*функция вывода массива*/
{
    for (int i = 0; i < k; i++)
    {
        printf("%s\n", s[i]);
    }
}


int input(char s1[][max_len], char **sp)
{
    int c = 0;
    char buf[max_len];
    while (c < max_str)
    {
        if (gets(buf) == NULL) {break;}

        int len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n')
        {
            buf[len-1] = '\0';
            len -= 1;
        }
        
        if (len == 0) {break;}

        strcpy(s1[c], buf);

        sp[c] = s1[c];
        c += 1;
    }
    return c;
}


int read(char *name, char s1[][max_len], char **sp)
{
    FILE *file;
	char buf[max_len];
    int c = 0;

	file = fopen(name, "r");
	if (!file) {exit(EXIT_FAILURE);}

    while (c < max_str)
    {
        if (fgets(buf, max_len, file) == NULL) {break;}

        int len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n')
        {
            buf[len-1] = '\0';
            len -= 1;
        }
        
        if (len == 0) {break;}

        strcpy(s1[c], buf);

        sp[c] = s1[c];
        c += 1;
    }
	fclose(file);
    return c;
}


void swap(char** x, char** y)
{
    char *temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


void quick_sort(char** sp, int first, int last)
{
    if (first >= last) return; 

    int l = first, r = last;
    char *pivot = sp[(l + r) / 2];
    
    while (l <= r)
    {
        while (strcmp(sp[l], pivot) < 0) l++;
        while (strcmp(sp[r], pivot) > 0) r--;
        
        if (l <= r)
        {
            swap(&sp[l], &sp[r]);
            l++;
            r--;
        }
    }
    if (first < r) { quick_sort(sp, first, r); }
    if (l < last) { quick_sort(sp, l, last); }
}


void distribute(char **sp, int c)
{
    if (c <= 0) return; // Проверка на пустой массив

    int count = 0;
    int step = c / 4; // Базовый размер группы

    int c1, c2, c3, c4;
    char s1 = 'A', s2, s3, s4;   // Первые буквы (начало группы)
    char ch1, ch2, ch3, ch4 = 'Z'; // Последние буквы (конец группы)
    int divv;

    divv = step;
    jump1:
    while (count < divv && count < c)
    {
        count++;
    }
    if (count < c && sp[count][0] == sp[count-1][0])
    {
        divv++;
        goto jump1;
    }
    c1 = count; 
    ch1 = sp[c1-1][0];

    s2 = sp[c1][0];
    divv = c1 + step;
    jump2:
    while (count < divv && count < c)
    {
        count++;
    }
    if (count < c && sp[count][0] == sp[count-1][0]) {
        divv++;
        goto jump2;
    }
    c2 = count;
    ch2 = sp[c2-1][0];

    s3 = sp[c2][0];
    divv = c2 + step;
    jump3:
    while (count < divv && count < c)
    {
        count++;
    }
    if (count < c && sp[count][0] == sp[count-1][0]) {
        divv++;
        goto jump3;
    }
    c3 = count;
    ch3 = sp[c3-1][0];

    s4 = sp[c3][0];
    while (count < c)
    {
        count++;
    }
    c4 = count;

    printf("%c-%c %d\n", s1, ch1, c1);
    printf("%c-%c %d\n", s2, ch2, c2 - c1);
    printf("%c-%c %d\n", s3, ch3, c3 - c2);
    printf("%c-%c %d\n", s4, ch4, c4 - c3);
}


int main()
{
    char s1[max_str][max_len];
    char *sp[max_str];

    //int c = read("1.txt", s1, sp);
    int c = input(s1, sp);
    quick_sort(sp, 0, c-1);
    output(sp, c);
    printf("\n");
    distribute(sp, c);
}