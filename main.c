#include "functions.h"

int main(int argc, char const *argv[])
{
	pthread_mutex_init(&mutex, NULL);
	srand(time(NULL));
	pthread_t p, f;
	pthread_t hora, ctrl;
	int prt, fr, hr, cnt;
	create_matrix(mat);
	
	FILE *log_fire, *log_thr;
	log_fire = fopen("fire.log", "w");
	fclose(log_fire);
	log_thr = fopen("threads.log", "w");
	fclose(log_thr);

	hr = pthread_create(&hora, NULL, update_time, NULL);
	if (hr){
		printf("ERROR! Could not create update_time thread. Return Code %d\n",hr);
		exit(-1);
	}
	prt = pthread_create(&p, NULL, print_matrix, NULL); 
	if (prt){
		printf("ERROR! Could not create print_matrix thread. Return Code %d\n",prt);
		exit(-1);
	}
	fr = pthread_create(&f, NULL, fire, NULL);
	if (fr){
		printf("ERROR! Could not create fire thread. Return Code %d\n",fr);
		exit(-1);
	}
	cnt = pthread_create(&ctrl, NULL, central, NULL);
	if (cnt){
		printf("ERROR! Could not create central thread. Return Code %d\n",cnt);
		exit(-1);
	}

	pthread_join(f,NULL);
	pthread_mutex_destroy(&mutex); 
	return 0;
}