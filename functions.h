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

char mat[TAM][TAM];

int hor,min,sec;

//TODO:
// Comunicação entre threads

typedef struct node
{
	int x,y;
	char up[10], down[10], left[10], right[10];
	char received[10], to_send[10];
	int id;
	int sent;
}Node;

Node nodes[THR][THR];

pthread_t sensor_threads[THR][THR];

sem_t mutex;
sem_t mutex_file;

void create_matrix(char mat[TAM][TAM]);
void *atualiza_hora(void *args);
void *print_matrix(void *args);
void *fire(void *args);
void *sensor_node(void *args);


#endif