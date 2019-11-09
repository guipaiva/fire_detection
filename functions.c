#include "functions.h"

void create_matrix(char mat[TAM][TAM]){
	memset(mat, '-', sizeof(mat[0][0])*TAM*TAM);
	int k = 0;
	int l = 0;
	int id = 1;
	for (int i = 1, l = 0; l < THR, i < TAM; l++, i+=3){
	 	for (int j = 1, k = 0; k < THR, j < TAM; k++, j +=3){
			mat[i][j] = 'T';
			nodes[l][k].x = i;
			nodes[l][k].y = j;
			nodes[l][k].id = id;
			id++;
			pthread_create(&sensor_threads[l][k], NULL, sensor_node, &nodes[l][k]);
	 	}
	}
}

void *atualiza_hora(void *args){
	while(1){
		sleep(1);
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		hor = tm.tm_hour;
		min = tm.tm_min;
		sec = tm.tm_sec;
	}
}	

void *print_matrix(void *args){
	//char (*mat)[TAM][TAM] = args;
	while(1)
	{
		system("clear");
		
		int idx, idy;
		int yes = 0;
		
		printf("\t");
		for (int i = 0; i < TAM; ++i)
		{
			if(i == 9)
				printf("9 ");
			else if(i < 10)
				printf("%d  ",i);
			else
				printf("%d ",i);
		}

		printf("\n");
		for (int i = 0; i < TAM; ++i)
		{
			printf("%d\t", i);
			for (int j = 0; j < TAM; ++j)
			{
				sem_wait(&mutex);
				if (mat[i][j] == '*') 
				{	
					idx = ((i+2)/3)-1;
					idy = ((j+2)/3)-1;
					yes = 1;
					mat[i][j] = 'X';
				}

				if (mat[i][j] == '/')
					printf("@  ");
				else
					printf("%c  ",mat[i][j]);
				sem_post(&mutex);
			}
			printf("\n");
		}

		printf("Hora: %02d:%02d:%02d\n",hor,min,sec);
		if (yes)
			printf("Thread n. %d foi destruida\n", nodes[idx][idy].id);
		yes = 0;
		sleep(1);
	}
}

void *fire(void *args){
	FILE *pont_arq1;
	int x,y;
	int idx, idy;
	while(1){
		sleep(3);
		x = rand()%30;
		y = rand()%30;
		sem_wait(&mutex); 
		if (mat[x][y] == 'T'){
			mat[x][y] = '*';
			idy = ((y+2)/3)-1;
			idx = ((x+2)/3)-1;
			pthread_cancel(sensor_threads[idx][idy]);
			pont_arq1 = fopen("arquivo1.txt", "a");
			fprintf(pont_arq1, "Thread %d destruida em %d:%d:%d\n", nodes[idx][idy].id,hor, min, sec);
			fclose(pont_arq1);
		}
		else
			mat[x][y] = '@';
		sem_post(&mutex);
	}
}

void *sensor_node(void *args){
	Node *sensor = args;
	FILE *pont_arq;
	while(1){
		for (int i = (sensor->x)-1; i <= (sensor->x) + 1; ++i)
		{
			for (int j = (sensor->y)-1; j <= (sensor->y) + 1; ++j)
			{
				if (i == j)
					continue;
				if (mat[i][j] == '@')
				{	
					mat[i][j] = '/';
					pont_arq = fopen("arquivo.txt", "a");
					fprintf(pont_arq, "Fogo em [%d][%d]. Thread %d. %d:%d:%d\n",i,j,sensor->id,hor, min, sec);
					fclose(pont_arq);
				}
			}
			sleep(1);
		}
	}
	return 0;
}
