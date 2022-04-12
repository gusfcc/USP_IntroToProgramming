//Gustavo Fernandes Carneiro de Castro - 11369684
//Renan Gomes Carneiro de Freitas - 11391085

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct movie {
	char* title;
	char* rating;
	char* ratingLevel;
	char* ratingDescription;
	char* release_year;
	char* user_rating_scores;
	char* user_rating_size;
} movie;

const char delim[2] = ";";

void ler(movie* filme);
void printar(movie* filme);
void faixa_etaria(movie* filme);
void filmes_ano(movie* filme);
void melhores_por_ano(movie* filme);
void violent_sexual_percent(movie* filme);
void keyword_search(movie* filme);


int main()
{
	movie filme[1001];
	char sel;
	int count_sel = 1;

	printf("Netflix file manipulator\n");
	printf("by: Gustavo and Renan");
	printf("\n______________________________________________________________________________");
	while(count_sel = 1)
	{
		printf("\n\n\nDigite:\n(1) Lista de filmes:\n(2) Número de filmes de cada faixa etária por ano:\n(3) Número de títulos lançados por ano:\n(4) Gerar um arquivo com os 10 melhores títulos de cada ano:\n(5) Mostrar o número de títulos violentos e com conteúdo sexual:\n(6) Procurar títulos por uma palavra chave\n(7) Sair:\n\n");
		scanf("%s",&sel);
	
		ler(filme);

		if (sel == '1')
			printar(filme);

		else if (sel == '2')
			faixa_etaria(filme);

		else if (sel == '3')
			filmes_ano(filme);

		else if (sel == '4')
			melhores_por_ano(filme);

		else if (sel == '5')
			violent_sexual_percent(filme);
	
		else if (sel == '6')
			keyword_search(filme);
	
		else if (sel == '7')
		{
			printf("\nAté logo!\n");
			exit(0);
		}
		else
		{
			printf("\nComando inválido!\n\n");
			count_sel = 1;
		}
	}
	return 0;
}

void printar(movie* filme)
{
	int i;
	for(i = 0; i <= 1000; i++)
	{
		printf("%d", i+1);
		printf("%s -", filme[i].title);
		printf(" %s -", filme[i].rating);
		printf(" %s -", filme[i].ratingLevel);
		printf(" %s -", filme[i].ratingDescription);
		printf(" %s -", filme[i].release_year);
		printf(" %s -", filme[i].user_rating_scores);
		printf(" %s\n\n", filme[i].user_rating_size);
	}
}

void ler(movie* filme)
{
	char aux[1000000];
    char* token;
	FILE* netflix = fopen("netflix_all.csv", "r");

	if (netflix == NULL)
	{
		printf("O arquivo não existe\n", setlocale(LC_ALL, "Portuguese"));
		exit(EXIT_FAILURE);
	}

	fread(aux, sizeof(char), 1000000, netflix);
	filme[0].title				    = strtok(aux, delim);
	filme[0].rating				    = strtok(NULL, delim);
    token                           = strtok(NULL, delim);
	if(!atoi(token))
    {
        filme[0].ratingLevel	    = token;
        filme[0].ratingDescription  = strtok(NULL, delim);
    }
    else
    {  
        filme[0].ratingLevel	    = "NA";
        filme[0].ratingDescription  = token;
    }
	filme[0].release_year		    = strtok(NULL, delim);
	filme[0].user_rating_scores     = strtok(NULL, delim);
	filme[0].user_rating_size	    = strtok(NULL, delim);

	for(int i = 1; i <= 1000; i++)
	{
		filme[i].title		        = strtok(NULL, delim);
		filme[i].rating				= strtok(NULL, delim);
		token                       = strtok(NULL, delim);
	if(!atoi(token))
    {
        filme[i].ratingLevel	    = token;
        filme[i].ratingDescription  = strtok(NULL, delim);
    }
    else
    {   
        filme[i].ratingLevel	    = "NA";
        filme[i].ratingDescription  = token;
    }
		filme[i].release_year		= strtok(NULL, delim);
		filme[i].user_rating_scores = strtok(NULL, delim);
		filme[i].user_rating_size	= strtok(NULL, delim);
	}
	fclose(netflix);
}

void filmes_ano(movie* filme)
{
	int year, i, counter = 0;

	for(year = 1940; year <= 2017; year++)
	{
		for (i = 1; i <= 1000; i++)
		{
			if(atoi(filme[i].release_year) == year)
				counter++;
		}
		printf("%d -- %4d filmes\n", year, counter);
		counter = 0;
	}
}

typedef struct nome_nota {
	int ano;
	int nota;
	char* nome;
} nomeNota;


void melhores_por_ano(movie* filme)
{
	nomeNota filmePorNota[1000], dezMelhores[10];
	int year, i, j, k, p, y, notaAux, token = 0;
	char*nomeAux;
	FILE* dez_melhores;

	for(i = 0; i <= 999; i++)
	{
		filmePorNota[i].ano = atoi(filme[i+1].release_year);
		filmePorNota[i].nota = atoi(filme[i+1].user_rating_scores);
		filmePorNota[i].nome = filme[i+1].title;
	}

	dez_melhores = fopen("dez_melhores", "w");

	for(year = 1940; year <= 2017; year++)
	{
		fprintf(dez_melhores, "\n\n%d", year);
		for (y = 0; y < 10; y++)
		{
			dezMelhores[y].nota = 0;
			dezMelhores[y].nome = "\n";
			dezMelhores[y].ano = year;
		}
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 1000; j++)
			{
				if(filmePorNota[j].ano == dezMelhores[i].ano && filmePorNota[j].nota > dezMelhores[i].nota)
				{
					dezMelhores[i].nome = filmePorNota[j].nome;
					dezMelhores[i].nota = filmePorNota[j].nota;

					nomeAux = filmePorNota[j].nome;
					notaAux = filmePorNota[j].nota;
				}
			}
			for(k = 0; k < 1000; k++)
			{
				if(!strcmp(filmePorNota[k].nome, nomeAux))
				{
					filmePorNota[k].nome = " ";
					filmePorNota[k].nota = 0;
				}
			}
		}
		for(p = 0; p < 10; p++)
			fprintf(dez_melhores, "%s - nota: %2d\n", dezMelhores[p].nome, dezMelhores[p].nota);
	}
	
	fclose(dez_melhores);

	system("gedit dez_melhores");
	
	
}

void faixa_etaria(movie* filme)
{
	int year, i;
	int pgT = 0, pgY = 0, r = 0, tvF = 0, pg = 0, tvMA = 0, tvY7FV = 0, g = 0;
	int tvY = 0, tvY7 = 0, nr = 0, tvPG = 0, tvG = 0, ur = 0;

	printf(" Ano | PG-13 | R | TV-14 | PG | TV-MA | TV-Y7-FV | G | TV-Y | TV-Y7 | NR | TV-PG | TV-G | UR |\n");

	for(year = 1940; year <= 2017; year++)
	{
		for (i = 1; i <= 1000; i++)
		{
			if(atoi(filme[i].release_year) == year)
			{
				if(!strcmp(filme[i].rating, "PG-13"))
					pgT++;
				else if(!strcmp(filme[i].rating, "R"))
					r++;
				else if(!strcmp(filme[i].rating, "TV-14"))
					tvF++;
				else if(!strcmp(filme[i].rating, "PG"))
					pg++;
				else if(!strcmp(filme[i].rating, "TV-MA"))
					tvMA++;
				else if(!strcmp(filme[i].rating, "TV-Y7-FV"))
					tvY7FV++;
				else if(!strcmp(filme[i].rating, "G"))
					g++;
				else if(!strcmp(filme[i].rating, "TV-Y"))
					tvY++;
				else if(!strcmp(filme[i].rating, "TV-Y7"))
					tvY7++;
				else if(!strcmp(filme[i].rating, "NR"))
					nr++;
				else if(!strcmp(filme[i].rating, "TV-PG"))
					tvPG++;
				else if(!strcmp(filme[i].rating, "TV-G"))
					tvG++;
				else if(!strcmp(filme[i].rating, "UR"))
					ur++;
			}
		}
		printf("%4d |    %3d|  %d|    %3d| %3d|    %3d|       %3d| %2d|   %3d|    %3d|  %2d|    %3d|   %3d| %3d|\n",
				year, pgT, r, tvF, pg, tvMA, tvY7FV, g, tvY, tvY7, nr, tvPG, tvG, ur);
		pgT = 0; pgY = 0; r = 0; tvF = 0; pg = 0; tvMA = 0; tvY7FV = 0; g = 0;
		tvY = 0; tvY7 = 0; nr = 0; tvPG = 0; tvG = 0; ur = 0;
	}
}

void violent_sexual_percent(movie* filme)
{
		char *findervio;
		char *findersex;
		int i, vio_count = 0, sex_count = 0;
		float vioper, sexper;

		for(i = 0; i <= 1000; i++)
		{
			if (findervio = strstr(filme[i].ratingLevel, "violence"))
			{
				vio_count++;
			}
			if (findersex = strstr(filme[i].ratingLevel, "sexual"))
			{
				sex_count++;
			}
		}
				vioper = ((float)vio_count / 1000) * 100;
				sexper = ((float)sex_count / 1000) * 100;

				printf("\nNúmero de filmes classificados com violência: %d, representando %.2f%% do total.\n", vio_count, vioper);
				printf("\nNúmero de filmes classificados com conteúdo sexual: %d, representando %.2f%% do total.\n\n", sex_count, sexper);
}

void keyword_search(movie* filme)
{
	char keyword[100];
	char *keyfinder;
	int i;

	printf("\nProcure seu filme por uma palavra-chave (Diferencie maiúsculas de minúsculas):\n\n");
	scanf("%s", &keyword);

	char *keypointer = keyword;
	const char *key = keypointer;

	printf("\n\nResultados para a palavra-chave %s:\n", keyword);

	for(i = 0; i <= 1000; i++)
	{
			if (keyfinder = strstr(filme[i].title, key))
			{
				printf("\n%s\n%s\n%s\n", keyfinder, filme[i].rating, filme[i].ratingLevel);
			}
		}
	}


