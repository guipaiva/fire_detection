#include "functions.h"

void create_matrix(char mat[MAX][MAX]){
	memset(mat, '-', sizeof(mat[0][0])*MAX*MAX);

	for (int i = 1; i < MAX; i+=3)
	 	for (int j = 1; j < MAX; j +=3)
			mat[i][j] = 'T';
}

void *print_matrix(void *args){
	char (*mat)[MAX][MAX] = args;
	while(1){
		system("clear");
		int hor,min,sec;
		time_t t = time(NULL);
	  	struct tm tm = *localtime(&t);
		hor = tm.tm_hour;
		min = tm.tm_min;
		sec = tm.tm_sec;
		printf("\t");
		for (int i = 0; i < MAX; ++i){
			if(i == 9)
				printf("9 ");
			else if(i < 10)
				printf("%d  ",i);
			else
				printf("%d ",i);
		}
		printf("\n");
		for (int i = 0; i < MAX; ++i)
		{
			printf("%d\t", i);
			for (int j = 0; j < MAX; ++j)
				printf("%c  ",(*mat)[i][j]);
			printf("\n");
		}
		printf("%02d:%02d:%02d\n",hor,min,sec);
		sleep(1);
	}
}

void *fire(void *args){
	char (*mat)[MAX][MAX] = args;
	int x,y;
	while(1){
		sleep(3);
		x = rand()%30;
		y = rand()%30;
		(*mat)[x][y] = '@';
	}
}

