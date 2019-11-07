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
#define NOS 10


//TODO:
// Matriz global
// Uma struct pra cada thread


struct nodes
{
	int x,y;
	//int fire;
	//char msg[4][10];
	int id;
}sensor[NOS][NOS];

typedef struct nodes sen_no;

pthread_t nodes[NOS][NOS];

sem_t mutex;

void create_matrix(char mat[TAM][TAM]);
void *print_matrix(void *args);
void *fire(void *args);
void *sensor_node(void *args);


#endif