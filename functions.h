#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#include <time.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h> 

#define TAM 30
#define THR 10

#define RED "\x1B[31m"
#define NRM "\x1B[0m"
#define BLK "\x1b[30m"
char mat[TAM][TAM];

int hor,min,sec;

//TODO:
// Comunicação entre threads

typedef struct node
{
	int x,y;
	int border;
	char up[16], down[16], left[16], right[16];
	int U, D, L, R;
	int id;
}Node;

Node nodes[THR][THR];

pthread_t sensor_threads[THR][THR];

sem_t mutex;

void create_matrix(char mat[TAM][TAM]);
void *atualiza_hora(void *args);
void *print_matrix(void *args);
void *fire(void *args);
void *sensor_node(void *args);
void send_msg(char msg[16], int x, int y);


#endif