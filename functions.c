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
			nodes[l][k].U = nodes[l][k].D = nodes[l][k].R = nodes[l][k].L = 0; 
			if (l == 0 || l == 9 || k == 0 || k == 9)
				nodes[l][k].border = 1;
			else
				nodes[l][k].border = 0;
			id++;
			pthread_create(&sensor_threads[l][k], NULL, sensor_node, &nodes[l][k]);
	 	}
	}
}

void send_msg(char *msg, int x, int y){
	FILE *f;
	f = fopen("teste.txt","a");
	fprintf(f,"%s %d %d\n",msg,x,y);
	fclose(f);

	if (nodes[x][y].border == 1)
		return;
/*	//TODO: REPLICATE
	//strncpy(string_destino, string_origem, tamanho);
*/

	//	Nó de cima
	strcpy(nodes[x-1][y].down,msg);
	nodes[x-1][y].D = 1;
	//	Nó de baixo
	strcpy(nodes[x+1][y].up,msg);
	nodes[x+1][y].U = 1;
	//	Nó da esquerda
	strcpy(nodes[x][y+1].left,msg);
	nodes[x][y+1].L = 1;
	// Nó da direita
	strcpy(nodes[x][y-1].right,msg);
	nodes[x][y-1].R = 1;
}

/*void rep_msg(){

}*/

void *atualiza_hora(void *args){
	while(1){
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		hor = tm.tm_hour;
		min = tm.tm_min;
		sec = tm.tm_sec;
		sleep(1);
	}
}	

void *print_matrix(void *args){
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
				printf("%s%d  ",NRM,i);
			else
				printf("%d ",i);
		}

		printf("\n");
		sem_wait(&mutex);
		for (int i = 0; i < TAM; ++i)
		{
			printf("%d\t", i);
			for (int j = 0; j < TAM; ++j)
			{
				
				if (mat[i][j] == '*') 
				{	
					idx = ((i+2)/3)-1;
					idy = ((j+2)/3)-1;
					yes = 1;
					mat[i][j] = 'X';
				}

				if (mat[i][j] == '/' || mat[i][j] == '@')
					printf("%s@%s  ",RED,NRM);
				else if (mat[i][j] == 'X')
					printf("%sX%s  ", BLK, NRM);
				else
					printf("%c  ",mat[i][j]);
				
			}
			printf("\n");
		}

		printf("Hora: %02d:%02d:%02d\n",hor,min,sec);
		if (yes)
			printf("Thread n. %d foi destruida\n", nodes[idx][idy].id);
		yes = 0;
		sem_post(&mutex);
		sleep(1);
	}
}

void *fire(void *args){
	FILE *log_thr;
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
			log_thr = fopen("threads.log", "a");
			fprintf(log_thr, "Thread %d destruida em %02d:%02d:%02d\n", nodes[idx][idy].id,hor, min, sec);
			fclose(log_thr);
		}
		else
			mat[x][y] = '@';
		sem_post(&mutex);
	}
}

void *sensor_node(void *args){
	Node *sensor = args;
	FILE *log_fire;
	char msg[16];
	int id;
	int idx, idy;
	int x, y;
	id = sensor->id;
	x = sensor->x;
	y = sensor->y;
	while(1){
		sem_wait(&mutex);
		//Replicate
		for (int i = x-1; i <= x + 1; ++i)
		{
			for (int j = x-1; j <= y + 1; ++j)
			{
				
				if (i == x && j == y)
					continue;
				if (mat[i][j] == '@')
				{	
					mat[i][j] = '/';
					sprintf(msg,"%03d%02d%02d%02d%02d%02d\n",id,i,j,hor,min,sec);
					idx = ((x+2)/3)-1;
					idy = ((y+2)/3)-1;
					send_msg(msg, idx, idy);
				}
			}
		}
		
		/*log_fire = fopen("incendios.log", "a");
		if ((sensor->U) == 1)
		fprintf(log_fire,"UP = %s ID = %d\n",(sensor->up),id);
		if ((sensor->D) == 1)
		fprintf(log_fire,"DOWN = %s ID = %d\n",(sensor->down),id);
		if ((sensor->L) == 1)
		fprintf(log_fire,"LEFT = %s ID = %d\n",(sensor->left),id);
		if ((sensor->R) == 1)
		fprintf(log_fire,"RIGHT = %s ID = %d\n",(sensor->right),id);
		//fprintf(log_fire, "Fogo em [%d][%d]. Thread %d. %02d:%02d:%02d\n",i,j,sensor->id,hor, min, sec);
		fclose(log_fire);*/
		sem_post(&mutex);
		sleep(1);
	}
	return 0;
}
