#include "functions.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	char mat[TAM][TAM];
	pthread_t p, f;
	int x,y;

	create_matrix(mat);
	sem_init(&mutex, 0, 1);
	
	pthread_create(&p, NULL, print_matrix, &mat); 
	pthread_create(&f, NULL, fire, &mat);

	pthread_join(f,NULL);	
	sem_destroy(&mutex);
	return 0;
}