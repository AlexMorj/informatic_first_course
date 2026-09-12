#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct workers
{
	char surname[20];
	char name[20];
	char town[20];
	char street[20];
	int dom;
	int kvart;
	char section[20];
	int ball;
};


void vstavka_nevozr(int *s, int l)
{
	for (int i = 1; i<l; i++)
	{
		int c = 0, m = s[i];
		while (c < i)
		{
			if (s[c] >= m ) {c += 1;}
			else {break;}
		}
		for (int k = i; k>c; k--)
		{
			s[k] = s[k-1];
		}
		s[c] = m;
	}
}


void vstavka_nevozr_towns(int *counts, char **towns, int l) /*функция "параллельной" сортировки
															двух массивов методом вставки*/
{
	for (int i = 1; i < l; i++)
	{
		int m_count = counts[i], c = 0;
		char *m_town = towns[i];
		while (c < i)
		{
			if (counts[c] >= m_count ) { c += 1; }
			else { break; }
		}
		for (int k = i; k > c; k--)
		{
			counts[k] = counts[k-1];
			towns[k] = towns[k-1];
		}
		counts[c] = m_count;
		towns[c] = m_town;
	}
}


// struct workers* read(char *name, int *len) 
// {
// 	FILE *file;
	
// 	file = fopen(name, "r");
// 	if (!file) {exit(EXIT_FAILURE);}
// 	fscanf(file, "%d", len);
// 	struct workers *arr = (struct workers*)malloc((*len) * sizeof(struct workers));
// 	if (arr == NULL) {exit(EXIT_FAILURE); }

//     for(int i = 0; i < (*len); i++)
//     {
//         fscanf(file, "%s %s %s %s %d %d %s %d",
// 			arr[i].surname,
// 			arr[i].name,
// 			arr[i].town,
// 			arr[i].street,
// 			&arr[i].dom,
// 			&arr[i].kvart,
// 			arr[i].section,
// 			&arr[i].ball);

//     }
// 	fclose(file);
// 	return arr;
// }


int main()
{
	int len, final;
	scanf("%d", &len);
	struct workers *arr = (struct workers*)malloc((len) * sizeof(struct workers));
	if (arr == NULL) {exit(EXIT_FAILURE); }
	for (int i = 0; i < len; i++)
	{
		scanf("%s %s %s %s %d %d %s %d",
			arr[i].surname,
			arr[i].name,
			arr[i].town,
			arr[i].street,
			&arr[i].dom,
			&arr[i].kvart,
			arr[i].section,
			&arr[i].ball);
	}
	scanf("%d", &final);


	char **s_section = NULL;
	int c = 0;
	for (int i = 0; i < len; i++) /*поиск всех уникальных секций*/
    {
		int f_dubl = 0;
        for (int j = 0; j < c; j++)
		{
			if (strcmp(s_section[j], arr[i].section) == 0)
			{
				f_dubl = 1;
				break;
			}
		}
		if (f_dubl == 0)
		{
			char **q = (char**)realloc(s_section, (c+1) * sizeof(char*)); 
			s_section = q;
			s_section[c] = (char*)malloc((strlen(arr[i].section) + 1) * sizeof(char));
            if (s_section[c] == NULL) { exit(EXIT_FAILURE); }
            strcpy(s_section[c], arr[i].section);
			c += 1;
		}
    }


	int prizes[c][len], people_per_section[c]; /*поиск всех "призеров" -- баллы каждого человека
												в распределении по секциям*/
	int colvo = 0;
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (strcmp(s_section[i], arr[j].section) == 0)
			{
				prizes[i][colvo] = arr[j].ball;
				colvo += 1;
			}
		}
		people_per_section[i] = colvo;
		colvo = 0;
	}


	int prohod_ball[c];
	for (int i = 0; i < c; i ++) /*поиск проходных баллов на каждую секцию*/
	{
		int cur = people_per_section[i];
		vstavka_nevozr(prizes[i], cur);
		if (cur <= final) {prohod_ball[i] = prizes[i][cur-1];}
		else {prohod_ball[i] = prizes[i][final-1];}
	}
	for (int i = 0; i < c; i ++)
	{
		printf("%s %d\n", s_section[i], prohod_ball[i]);
	}
	printf("\n"); 


	char **s_surname = NULL;
	int numb_surnames = 0;
	for (int i = 0; i < c; i++) /*вывод фамилий финалистов по каждой дисциплине
								и создание массива фамилий финалистов*/
	{
		printf("%s\n", s_section[i]);
		for (int j = 0; j < len; j++)	
		{
			if (strcmp(s_section[i], arr[j].section) == 0 && arr[j].ball >= prohod_ball[i])
			{
				printf(" %s\n", arr[j].surname); 
				
				char **p = (char**)realloc(s_surname, (numb_surnames+1) * sizeof(char*));
				if (p==NULL) {exit (EXIT_FAILURE);}
				s_surname = p;
				s_surname[numb_surnames] = (char*)malloc((strlen(arr[j].surname) + 1) * sizeof(char));
				if (s_surname[numb_surnames] == NULL) { exit(EXIT_FAILURE); }
				strcpy(s_surname[numb_surnames], arr[j].surname);
				numb_surnames += 1;
			}
		}
	}
	printf("\n"); 


	char **s_all_towns = NULL;
	int c_all_towns = 0;
	for (int i = 0; i < len; i++) /*поиск всех уникальных городов (по аналогии с секциями)*/
	{
		int f_dubl = 0;
		for (int j = 0; j < c_all_towns; j++)
		{
			if (strcmp(s_all_towns[j], arr[i].town) == 0)
			{
				f_dubl = 1;
				break;
			}
		}
		if (f_dubl == 0)
		{
			char **q = (char**)realloc(s_all_towns, (c_all_towns+1) * sizeof(char*)); 
			s_all_towns = q;
			s_all_towns[c_all_towns] = (char*)malloc((strlen(arr[i].town) + 1) * sizeof(char));
			if (s_all_towns[c_all_towns] == NULL) { exit(EXIT_FAILURE); }
			
			strcpy(s_all_towns[c_all_towns], arr[i].town);
			c_all_towns += 1;
		}
	}

	char **s_fin_towns = (char**)malloc(numb_surnames * sizeof(char*));
	if (s_fin_towns == NULL) { exit(EXIT_FAILURE); }

	for (int i = 0; i < numb_surnames; i++) /*поиск города для каждого финалиста*/
	{
		for (int j = 0; j < len; j++)
		{
			if (strcmp(s_surname[i], arr[j].surname) == 0)
			{
				s_fin_towns[i] = (char*)malloc((strlen(arr[j].town) + 1) * sizeof(char));
				if (s_fin_towns[i] == NULL) { exit(EXIT_FAILURE); }
				
				strcpy(s_fin_towns[i], arr[j].town);
				break;
			}
		}
	}

	char **s_ans_towns = NULL;
	int *ans_counts = NULL;
	int c_ans = 0;

	for (int i = 0; i < c_all_towns; i++) /*поиск пересечений уникальных городов и городов-финалистов,
											чтобы создать массив УНИКАЛЬНЫХ городов-финалистов
											(те уникальные города, в которых есть финалисты). при этом
											количество "пересечений названия уникального города и 
											города-финалиста даст количество финалистов в каждом 
											уникальном городе-финалисте"*/
	{
		int colvo = 0;
		for (int j = 0; j < numb_surnames; j++)
		{
			if (strcmp(s_all_towns[i], s_fin_towns[j]) == 0)
			{
				colvo += 1;
			}
		}
		if (colvo > 0)
		{
			char **q = (char**)realloc(s_ans_towns, (c_ans+1) * sizeof(char*));
			s_ans_towns = q;
			s_ans_towns[c_ans] = (char*)malloc((strlen(s_all_towns[i]) + 1) * sizeof(char));
			strcpy(s_ans_towns[c_ans], s_all_towns[i]);

			int *p = (int*)realloc(ans_counts, (c_ans+1) * sizeof(int));
			ans_counts = p;
			ans_counts[c_ans] = colvo;

			c_ans += 1;
		}
	}
	printf("%d\n\n", c_ans);
	vstavka_nevozr_towns(ans_counts, s_ans_towns, c_ans);

	for (int i = 0; i < c_ans; i++)
	{
		if (i < c_ans-1)
		{
			printf("%s ", s_ans_towns[i]);
		}
		else if (i == c_ans-1)
		{
			printf("%s\n", s_ans_towns[i]); 
		}
	}
	free(arr);

	for (int i = 0; i < c; i++) {
		free(s_section[i]);
	}
	free(s_section);

	for (int i = 0; i < numb_surnames; i++) {
		free(s_surname[i]);
		free(s_fin_towns[i]);
	}
	free(s_surname);
	free(s_fin_towns);

	for (int i = 0; i < c_all_towns; i++) {
		free(s_all_towns[i]);
	}
	free(s_all_towns);

	for (int i = 0; i < c_ans; i++) {
		free(s_ans_towns[i]);
	}
	free(s_ans_towns);
	free(ans_counts);
}