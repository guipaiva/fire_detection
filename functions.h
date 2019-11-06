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

struct nodes
{
	int x,y;
	/*int fire;
	char msg[10];*/
	int id;
}sensor[NOS][NOS];

sem_t mutex;

void create_matrix(char mat[TAM][TAM]);
void *print_matrix(void *args);
void *fire(void *args);
void *check_fire(void *args);


#endif