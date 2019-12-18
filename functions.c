#include "functions.h"

int convert_x(int id){
	int x;
	if (id % 10 == 0)
		id--;
	x = 3*(id/10) +1;
	return x;
}

int convert_y(int id){
	int y;
	if (id % 10 == 0){
		y = 28;
		return y;
	}
	y = 3 * (id%10) - 2;
	return y;
}

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
			nodes[l][k].U = nodes[l][k].D = nodes[l][k].R = nodes[l][k].L = nodes[l][k].C = 0; 
			nodes[l][k].live = 1;

			if (l == 0 || l == 9 || k == 0 || k == 9)
				nodes[l][k].border = 1;
			else
				nodes[l][k].border = 0;
			id++;
			pthread_create(&sensor_threads[l][k], NULL, sensor_node, (void *)(intptr_t)id);
	 	}
	}
}


void send_msg(int x, int y){
	if (nodes[x][y].border == 1)
		return;
	
	nodes[x][y].C = 0;

	//	Nó de cima
	memcpy(nodes[x-1][y].down, nodes[x][y].center, sizeof(nodes[x][y].center));
	nodes[x-1][y].D = 1;
	
	//	Nó de baixo
	memcpy(nodes[x+1][y].up, nodes[x][y].center, sizeof(nodes[x][y].center));
	nodes[x+1][y].U = 1;
	
	//	Nó da direita
	memcpy(nodes[x][y+1].left, nodes[x][y].center, sizeof(nodes[x][y].center));
	nodes[x][y+1].L = 1;
	
	// Nó da esquerda
	memcpy(nodes[x][y-1].right, nodes[x][y].center, sizeof(nodes[x][y].center));
	nodes[x][y-1].R = 1;
}

void prop_msg(int x, int y){
	if (nodes[x][y].border == 1)
		return;
	int ok = 0;
	size_t size = sizeof(nodes[x][y].center);
	if (nodes[x][y].U == 1) //Recebeu de cima, manda para todos os outros
	{
		nodes[x][y].U = 0;
		memcpy(nodes[x+1][y].up, nodes[x][y].up,size); //Nó de baixo
		nodes[x+1][y].U = 1;
		memcpy(nodes[x][y+1].left, nodes[x][y].up,size); //Nó da direita
		nodes[x][y+1].L = 1;
		memcpy(nodes[x][y-1].right, nodes[x][y].up,size); //Nó da esquerda
		nodes[x][y-1].R = 1;
		ok = 1;
	}
	else if (nodes[x][y].D == 1) //Recebeu de baixo, manda para todos os outros
	{
		nodes[x][y].D = 0;
		memcpy(nodes[x-1][y].down, nodes[x][y].down,size); //Nó de cima
		nodes[x-1][y].D = 1;
		memcpy(nodes[x][y+1].left, nodes[x][y].down,size); //Nó da direita
		nodes[x][y+1].L = 1;
		memcpy(nodes[x][y-1].right, nodes[x][y].down,size); //Nó da esquerda
		nodes[x][y-1].R = 1;
		ok = 1;
	}
	else if (nodes[x][y].L == 1) //Recebeu da esquerda, manda para todos os outros
	{
		nodes[x][y].L = 0;
		memcpy(nodes[x-1][y].down, nodes[x][y].left,size); //Nó de cima
		nodes[x-1][y].D = 1;
		memcpy(nodes[x+1][y].up, nodes[x][y].left,size); //Nó de baixo
		nodes[x+1][y].U = 1;
		memcpy(nodes[x][y+1].left, nodes[x][y].left,size); //Nó da direita
		nodes[x][y+1].L = 1;
		ok = 1;
	}
	else if (nodes[x][y].R == 1) //Recebeu da direita, manda para todos os outros
	{
		nodes[x][y].R = 0;
		memcpy(nodes[x-1][y].down, nodes[x][y].right,size); //Nó de cima
		nodes[x-1][y].D = 1;
		memcpy(nodes[x+1][y].up, nodes[x][y].right,size); //Nó de baixo
		nodes[x+1][y].U = 1;
		memcpy(nodes[x][y-1].right, nodes[x][y].right,size); //Nó da esquerda
		nodes[x][y-1].R = 1;
		ok = 1;
	}
	if(ok)
		sleep(1);
}
void clear_msg(int msg[6]){
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (memcmp(msg,nodes[i][j].up,sizeof(msg[0])*6) == 0){
				nodes[i][j].U = 0;
			}
			else if (memcmp(msg,nodes[i][j].down,sizeof(msg[0])*6) == 0){
				nodes[i][j].D = 0;
			}
			else if (memcmp(msg,nodes[i][j].left,sizeof(msg[0])*6) == 0){
				nodes[i][j].L = 0;
			}
			else if (memcmp(msg,nodes[i][j].right,sizeof(msg[0])*6) == 0){
				nodes[i][j].R = 0;
			}
			else if (memcmp(msg,nodes[i][j].center,sizeof(msg[0])*6) == 0){
				nodes[i][j].C = 0;
			}
		}
	}

}

void firefighter(int x, int y){
	//sleep(2);
	if (mat[x][y] == '/' || mat[x][y] == '@')
		mat[x][y] = '-';
}

void *update_time(void *args){
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
		pthread_mutex_lock(&mtx_prt);
		printf(BGGRN);
		system("clear");
		int idx, idy;
		int yes = 0;
		printf("\t");
		for (int i = 0; i < TAM; ++i)
		{
			if(i == 9)
				printf("%s9 ",WHT);
			else if(i < 10)
				printf("%s%d  ",WHT,i);
			else
				printf("%s%d ",WHT,i);
		}

		printf("\n");
		
		for (int i = 0; i < TAM; ++i)
		{
			printf("%s%d%s\t",WHT,i,BLK);
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
					printf("%s@%s  ",RED,WHT);
				else if (mat[i][j] == 'X')
					printf("%sX%s  ",GRY,WHT);
				else
					printf("%s%c  ",BLK,mat[i][j]);
				
			}
			printf("\n");
		}

		printf("%sTime: %02d:%02d:%02d\n",WHT,hor,min,sec);
		if (yes)
			printf("%sThread #%d has been destroyed\n",WHT,nodes[idx][idy].id);
		yes = 0;
		pthread_mutex_unlock(&mtx_prt);
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
		pthread_mutex_lock(&mtx_prt); 
		if (mat[x][y] == 'T'){
			mat[x][y] = '*';
			idy = ((y+2)/3)-1;
			idx = ((x+2)/3)-1;
			nodes[idx][idy].live = 0;
			//pthread_cancel(sensor_threads[idx][idy]);
			log_thr = fopen("threads.log", "a");
			fprintf(log_thr, "Thread #%d was destroyed at %02d:%02d:%02d\n", nodes[idx][idy].id,hor, min, sec);
			fclose(log_thr);
		}
		else if (mat[x][y] == 'X'){}
		else
			mat[x][y] = '@';
		pthread_mutex_unlock(&mtx_prt);
	}
}

void *sensor_node(void *args){
	int id = (intptr_t) args;
	int idx, idy;
	int x, y;
	int sent;
	x = convert_x(id);
	y = convert_y(id);
	idx = ((x+2)/3)-1;
	idy = ((y+2)/3)-1;
	while(1){
		if (nodes[idx][idy].live == 1)
		{
			sent = 0;
			pthread_mutex_lock(&mutex);
			for (int i = x-1; i <= x + 1; ++i)
			{
				for (int j = y-1; j <= y + 1; ++j)
				{			
					if (i == x && j == y)
						continue;
					if (mat[i][j] == '@')
					{	
						mat[i][j] = '/';
						nodes[idx][idy].center[0] = nodes[idx][idy].id;
						nodes[idx][idy].center[1] = i;
						nodes[idx][idy].center[2] = j;
						nodes[idx][idy].center[3] = hor;
						nodes[idx][idy].center[4] = min;
						nodes[idx][idy].center[5] = sec;
						nodes[idx][idy].C = 1;
						if(nodes[idx][idy].border == 0){	
							send_msg(idx, idy);
							sent = 1;
						}
					}
				}
			}
			if(sent == 0)
				prop_msg(idx,idy);
			
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}
	}
}

void *central(void *args){
	int msg[6];
	size_t size = sizeof(msg);
	FILE *log_fire;
	while(1){
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (nodes[i][j].border == 0)
					continue;

				if (nodes[i][j].U == 1){
					nodes[i][j].U = 0;
					log_fire = fopen("fire.log", "a");
					memcpy(msg, nodes[i][j].up, size);
					fprintf(log_fire,"Central %02d:%02d:%02d\n",hor,min,sec);
					fprintf(log_fire,"Thread #%d detected a fire at [%d][%d]",msg[0],msg[1],msg[2]);
					fprintf(log_fire," at %02d:%02d:%02d\n\n",msg[3],msg[4],msg[5]);
					fclose(log_fire);
					clear_msg(msg);				
					firefighter(msg[1],msg[2]);
				}
				else if (nodes[i][j].D == 1){
					nodes[i][j].D = 0;
					log_fire = fopen("fire.log", "a");
					memcpy(msg, nodes[i][j].down, size);
					fprintf(log_fire,"Central %02d:%02d:%02d\n",hor,min,sec);
					fprintf(log_fire,"Thread #%d detected a fire at [%d][%d]",msg[0],msg[1],msg[2]);
					fprintf(log_fire," at %02d:%02d:%02d\n\n",msg[3],msg[4],msg[5]);
					fclose(log_fire);					
					clear_msg(msg);				
					firefighter(msg[1],msg[2]);
				}
				else if (nodes[i][j].L == 1){
					nodes[i][j].L = 0;
					log_fire = fopen("fire.log", "a");
					memcpy(msg, nodes[i][j].left, size);
					fprintf(log_fire,"Central %02d:%02d:%02d\n",hor,min,sec);
					fprintf(log_fire,"Thread #%d detected a fire at [%d][%d]",msg[0],msg[1],msg[2]);
					fprintf(log_fire," at %02d:%02d:%02d\n\n",msg[3],msg[4],msg[5]);
					fclose(log_fire);					
					clear_msg(msg);				
					firefighter(msg[1],msg[2]);
				}
				else if (nodes[i][j].R == 1){
					nodes[i][j].R = 0;
					log_fire = fopen("fire.log", "a");
					memcpy(msg, nodes[i][j].right, size);
					fprintf(log_fire,"Central %02d:%02d:%02d\n",hor,min,sec);
					fprintf(log_fire,"Thread #%d detected a fire at [%d][%d]",msg[0],msg[1],msg[2]);
					fprintf(log_fire," at %02d:%02d:%02d\n\n",msg[3],msg[4],msg[5]);
					fclose(log_fire);					
					clear_msg(msg);				
					firefighter(msg[1],msg[2]);
				}
				else if (nodes[i][j].C == 1){
					nodes[i][j].C = 0;
					log_fire = fopen("fire.log", "a");
					memcpy(msg, nodes[i][j].center, size);
					fprintf(log_fire,"Central %02d:%02d:%02d\n",hor,min,sec);
					fprintf(log_fire,"Thread #%d detected a fire at [%d][%d]",msg[0],msg[1],msg[2]);
					fprintf(log_fire," at %02d:%02d:%02d\n\n",msg[3],msg[4],msg[5]);
					fclose(log_fire);					
					clear_msg(msg);			
					firefighter(msg[1],msg[2]);
				}
			}
		}
		sleep(1);
	}
}
