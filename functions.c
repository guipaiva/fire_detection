#include "functions.h"

void create_matrix(char mat[TAM][TAM]){
	memset(mat, '-', sizeof(mat[0][0])*TAM*TAM);
	int k = 0;
	for (int i = 1; i < TAM; i+=3){
	 	for (int j = 1; j < TAM; j +=3){
			mat[i][j] = 'T';
			sensor[k].x = i;
			sensor[k].y = j;
			k++;
	 	}
	}
}	

void *print_matrix(void *args){
	char (*mat)[TAM][TAM] = args;
	while(1){
		system("clear");
		int hor,min,sec;
		time_t t = time(NULL);
	  	struct tm tm = *localtime(&t);
		hor = tm.tm_hour;
		min = tm.tm_min;
		sec = tm.tm_sec;
		printf("\t");
		for (int i = 0; i < TAM; ++i){
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
			for (int j = 0; j < TAM; ++j){
				sem_wait(&mutex);
				printf("%c  ",(*mat)[i][j]);
				sem_post(&mutex);
			}
			printf("\n");
		}
		printf("Hora: %02d:%02d:%02d\n",hor,min,sec);
		sleep(1);
	}
}

void *fire(void *args){
	char (*mat)[TAM][TAM] = args;
	int x,y;
	while(1){
		sleep(3);
		x = rand()%30;
		y = rand()%30;
		sem_wait(&mutex); 
		(*mat)[x][y] = '@';
		sem_post(&mutex);
	}
}

void *check_fire(void *args){
	
}
