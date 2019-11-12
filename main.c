#include "functions.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	pthread_t p, f;
	pthread_t hora;

	create_matrix(mat);
	sem_init(&mutex, 0, 1);

	FILE *log_fire, *log_thr;
	log_fire = fopen("incendios.log", "w");
	fclose(log_fire);
	log_thr = fopen("threads.log", "w");
	fclose(log_thr);
	pthread_create(&hora, NULL, atualiza_hora, NULL);
	pthread_create(&p, NULL, print_matrix, NULL); 
	pthread_create(&f, NULL, fire, NULL);
	pthread_join(f,NULL);
	sem_destroy(&mutex);
	return 0;
}