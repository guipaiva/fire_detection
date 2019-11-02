#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <time.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define MAX 30

void create_matrix(char mat[MAX][MAX]);
void *print_matrix(void *args);
void *fire(void *args);

#endif