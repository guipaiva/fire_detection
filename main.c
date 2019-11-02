#include "functions.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	char mat[MAX][MAX];
	create_matrix(mat);
	pthread_t p, f;
	pthread_create(&p, NULL, print_matrix, &mat); 
	pthread_create(&f, NULL, fire, &mat);

	pthread_join(p, NULL);

	return 0;
}