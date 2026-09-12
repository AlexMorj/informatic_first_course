#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct workers
{
	char surname[20];
	char name[20];
	int department_number;
	int salary;
	int bonus;
	int taxes;
};


int main()
{
	int n;
	scanf("%d", &n);

	struct workers* arr = malloc(n * sizeof(struct workers));
	if (arr == NULL) { exit(EXIT_FAILURE); }

	for (int i = 0; i< n; i++)
	{
		scanf("%s %s %d %d %d %d",
			arr[i].surname,
			arr[i].name,
			&arr[i].department_number,
			&arr[i].salary,
			&arr[i].bonus,
			&arr[i].taxes);
	}

	for (int i = 0; i < n; i++)
	{
		printf("%-15s%-15s%5d%5d%5d%5d\n",
			arr[i].surname,
			arr[i].name,
			arr[i].department_number,
			arr[i].salary,
			arr[i].bonus,
			arr[i].taxes);
	}
	printf("\n");

	int F = 0, minn = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		if (arr[i].department_number == 1)
		{
			if (arr[i].salary + arr[i].bonus - arr[i].taxes <= minn)
			{
				F = 1;
				minn = arr[i].salary + arr[i].bonus - arr[i].taxes;
			}
		}
	}
	
	if (F == 1)
	{
		for (int i = 0; i < n; i++)
		{
			if (arr[i].department_number == 1)
			{
				if (arr[i].salary + arr[i].bonus - arr[i].taxes == minn)
				{
					printf("%s %s\n", arr[i].surname, arr[i].name);
				}
			}
		}
		printf("\n");

		for (int i = 0; i < n; i++)
		{
			if (arr[i].department_number == 1)
			{
				if (arr[i].salary + arr[i].bonus - arr[i].taxes < minn)
				{
					printf("%s %s\n", arr[i].surname, arr[i].name);
				}
			}
			if (arr[i].department_number != 1)
			{
				if (arr[i].salary + arr[i].bonus - arr[i].taxes <= minn)
				{
					printf("%s %s\n", arr[i].surname, arr[i].name);
				}
			}
		}
	}
	free(arr);
}