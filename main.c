#include "functions.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	pthread_t p, f;
	pthread_t hora;
	int x,y;

	create_matrix(mat);
	sem_init(&mutex, 0, 1);

	FILE *log_fire, *log_thr;
	log_fire = fopen("incendios.log", "w");
	log_thr = fopen("threads.log", "w");
	pthread_create(&hora, NULL, atualiza_hora, NULL);
	pthread_create(&p, NULL, print_matrix, NULL); 
	pthread_create(&f, NULL, fire, NULL);
	pthread_join(f,NULL);
	sem_destroy(&mutex);
	return 0;
}