#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <time.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define TAM 30
#define THR 10

#define RED "\e[31m"
#define WHT "\e[97m"
#define BLK "\e[30m"
#define BGGRN "\e[48;5;28m"
#define GRY "\e[38;5;252m"

char mat[TAM][TAM];

int hor,min,sec;


typedef struct node
{
	int x,y;
	int border;
	int up[6], down[6], left[6], right[6], center[6];
	int U, D, L, R, C;
	int id;
	int live;
}Node;

Node nodes[THR][THR];

pthread_t sensor_threads[THR][THR];

pthread_mutex_t mutex, mtx_prt; 

void create_matrix(char mat[TAM][TAM]);
void *update_time(void *args);
void *print_matrix(void *args);
void *fire(void *args);
void *sensor_node(void *args);
void *central (void *args);
void send_msg(int x, int y);
void prop_msg(int x, int y);
void clear_msg(int msg[6]);
void firefighter(int x, int y);
int converte_x(int id);
int converte_y(int id);


#endif
