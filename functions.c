#include "functions.h"

void create_matrix(char mat[TAM][TAM]){
	memset(mat, '-', sizeof(mat[0][0])*TAM*TAM);
	int k = 0;
	int l = 0;
	int id = 1;
	for (int i = 1, l = 0; l < NOS, i < TAM; l++, i+=3){
	 	for (int j = 1, k = 0; k < NOS, j < TAM; k++, j +=3){
			mat[i][j] = 'T';
			sensor[l][k].x = i;
			sensor[l][k].y = j;
			sensor[l][k].id = id;
			id++;
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
	int idx, idy;
	while(1){
		sleep(3);
		x = rand()%30;
		y = rand()%30;
		sem_wait(&mutex); 
		if ((*mat)[x][y] == 'T'){
			(*mat)[x][y] = 'X';
			//coordenada da thread que irá destruir;
			idy = ((y+2)/3)-1;
			idx = ((x+2)/3)-1;
			printf("Thread n. %d foi destruida\n", sensor[idx][idy].id);
			pthread_cancel(nodes[idx][idy]);
		}
		else
			(*mat)[x][y] = '@';
		sem_post(&mutex);
	}
}

void *check_fire(void *args){
	
}
