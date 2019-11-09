#include "functions.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	pthread_t p, f;
	pthread_t hora;
	int x,y;

	create_matrix(mat);
	sem_init(&mutex, 0, 1);

	FILE *pont_arq, *pont_arq1;
	pont_arq = fopen("arquivo.txt", "w");
	pont_arq1 = fopen("arquivo1.txt", "w");
	pthread_create(&hora, NULL, atualiza_hora, NULL);
	pthread_create(&p, NULL, print_matrix, NULL); 
	pthread_create(&f, NULL, fire, NULL);
	pthread_join(f,NULL);
	sem_destroy(&mutex);
	return 0;
}