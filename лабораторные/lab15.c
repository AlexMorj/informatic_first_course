#include <stdio.h>
#include <stdlib.h>


void full_index (int **a, int n, int m)
{
    for (int i = n-1; i >= 0; i--)
	{
		int q = (n - i - 1) % 2;

		if (q == 0)
		{
			for (int j = 0; j < m; j++)
			{
				scanf("%d", &a[i][j]);
			}
		}
		else
		{
			for (int j = m-1; j >= 0; j--)
			{
				scanf("%d", &a[i][j]);
			}
		}
	}
}


void full_adress (int **a, int n, int m)
{
    for (int i = n-1; i >= 0; i--)
	{
		int q = (n - i - 1) % 2;

		if (q == 0)
		{
			for (int j = 0; j < m; j++)
			{
				scanf("%d", *(a+i)+j);
			}
		}
		else
		{
			for (int j = m-1; j >= 0; j--)
			{
				scanf("%d", *(a+i)+j);
			}
		}
	}
}


void output_index(int **a, int n, int m)
{
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}


void output_adress(int **a, int n, int m)
{
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%3d", *(*(a+i)+j));
		}
		printf("\n");
	}
}


void minn_summ_index(int **a, int n, int m, int *c, int *str_max)
{
    int minn = 1000000, *str_summ;
    str_summ = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        str_summ[i] = 0;
        for (int j = 0; j < m; j++)
        {
            str_summ[i] += a[i][j];
        }
        if (str_summ[i] <= minn)
        {
            minn = str_summ[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (str_summ[i] == minn)
        {
            str_max[*c] = i+1;
            (*c) += 1;
        }
    }
    free(str_summ);
}


void minn_summ_adress(int **a, int n, int m, int *c, int *str_max)
{
    int minn = 1000000, *str_summ;
    str_summ = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        *(str_summ + i) = 0;
        for (int j = 0; j < m; j++)
        {
            *(str_summ + i) += *(*(a+i)+j);
        }
        if (*(str_summ + i) <= minn)
        {
            minn = *(str_summ + i);
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (*(str_summ + i) == minn)
        {
            *(str_max+*c) = i+1;
            (*c) += 1;
        }
    }
    free(str_summ);
}


int minn_index(int *s, int l)
{
    int minn = 10000;
    for (int i = 0; i < l; i++) 
    {
        if (s[i] < minn)
        {
            minn = s[i];
        }
    }
    return minn;
}


int minn_adress(int *s, int l)
{
    int minn = 10000;
    for (int i = 0; i < l; i++) 
    {
        if (*(s+i) < minn)
        {
            minn = *(s+i);
        }
    }
    return minn;
}


void sedl_index(int **a, int n, int m)
{
    int *minn_str, *maxx_stl, maxx = -1000, sedl = 0, c = 0;

    minn_str = (int*)malloc(n*sizeof(int));
    maxx_stl = (int*)malloc(m*sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        minn_str[i] = minn_index(a[i], m);
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i][j] > maxx) {maxx = a[i][j];}
        }
        maxx_stl[j]= maxx;
        maxx = -1000;
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == minn_str[i] && a[i][j] == maxx_stl[j])
            {
                sedl = minn_str[i];
                c += 1;
            }
        }
    }

    if (c > 1) {printf("%d %d\n", sedl, c);}
    else if (c == 1) {printf("%d\n", sedl);}
    else {printf("-\n");}
    
    free(maxx_stl);
    free(minn_str);
}


void sedl_adress(int **a, int n, int m)
{
    int *minn_str, *maxx_stl, maxx = -1000, sedl = 0, c = 0;

    minn_str = (int*)malloc(n*sizeof(int));
    maxx_stl = (int*)malloc(m*sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        *(minn_str+i) = minn_adress(*(a+i), m);
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (*(*(a+i)+j) > maxx) {maxx = *(*(a+i)+j);}
        }
        *(maxx_stl+j) = maxx;
        maxx = -1000;
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (*(*(a+i)+j) == *(minn_str+i) && *(*(a+i)+j) == *(maxx_stl + j))
            {
                sedl = *(minn_str+i);
                c += 1;
            }
        }
    }

    if (c > 1) {printf("%d %d\n", sedl, c);}
    else if (c == 1) {printf("%d\n", sedl);}
    else {printf("-\n");}
    
    free(maxx_stl);
    free(minn_str);
}


int main()
{
	int **a, m, n, c = 0, str_max[1000]={0};
	scanf("%d %d", &n, &m);

    int F = 0; /*поменять на 1 для "адресного" исполнения программы*/

	a = (int**)malloc(n * sizeof(int*) + n * m * sizeof(int));
	if (a == NULL) { exit(EXIT_FAILURE); }
	for (int i = 0; i < n; ++i)
	{
        a[i] = (int*)(a + n) + i * m;
    }

    if (F == 0)
    {
        full_index(a, n, m);
        minn_summ_index(a, n, m, &c, str_max);
        output_index(a, n, m);
        printf("\n");

        for (int t = 0; t < c; t++)
        {
            if(t != c-1) {printf("%d ", str_max[t]);}
            else if (t == c-1) {printf("%d\n", str_max[t]);}
        }
        sedl_index(a, n, m);
    }
    else
    {
        full_adress(a, n, m);
        minn_summ_adress(a, n, m, &c, str_max);
        output_adress(a, n, m);
        printf("\n");

        for (int t = 0; t < c; t++)
        {
            if(t != c-1) {printf("%d ", *(str_max + t));}
            else if (t == c-1) {printf("%d\n", *(str_max + t));}
        }
        sedl_adress(a, n, m);
    }
	free(a);
}