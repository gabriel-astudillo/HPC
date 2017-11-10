#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int num_steps;
int num_th;

double calc_pi(int inf, int sup){
	double sum;
	double x,step;
	int i;

	step = 1.0/(double) num_steps;
	sum  = 0.0;
	#pragma omp parallel private(x) num_threads(num_th)
	{
		#pragma omp for reduction(+:sum)
		for (i = inf; i < sup; i++){
		  x = (i+step/2.0)*step;
		  //sum = sum + 4.0/(1.0+x*x)*step;
		  sum += 4*sqrt( 1.0-x*x )*step;
		}
	}


	return(sum);
}

int main (int argc, char** argv) {
	  double pi;

	  if(argc!=3){
	    printf("Faltan parametros\n");
	    exit(EXIT_FAILURE);
	  }

	  num_steps = atoi(argv[1]);
	  num_th = atoi(argv[2]);

	  pi = calc_pi(0,num_steps);

	  printf("\nPI = %.10f Error: %.10f \n",pi, pi-M_PI);

	  exit(EXIT_SUCCESS);
}
