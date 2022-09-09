#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define N 512        
#define LOOPS 10
#define B 32  //Block size for blocked multiplication
#define THREADBLOCK 128 // block size for threaded multiplication (number of rows of c per thread)
#define NTHREADS N/THREADBLOCK

double a[N][N]; /* input matrix */
double b[N][N]; /* input matrix */
double c[N][N]; /* result matrix */

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

//Function executed by each thread. Each thread will carry out the computation of THREADBLOCK rows of c
void* thread_multi(void* arg){
  int threadid = (int) arg, i, j ,k;

  for(i=threadid*THREADBLOCK; i<(threadid+1)*THREADBLOCK; i++){
    for(j=0; j<N; j++){
      for(k=0; k<N; k++){
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

}

int main()
{
  int i,j,k,l, num_zeros, kk, jj;
  double start, finish, total, sum;

  /* initialize a dense matrix */
  for(i=0; i<N; i++){    
    for(j=0; j<N; j++){
      a[i][j] = (double)(i+j);
      b[i][j] = (double)(i-j);
    }
  }
  
  printf("\nOPTIMIZED MATRIX MULTIPLICATION\n");

  //The following lines of code correspond to the implementation of a sequential blocked matrix multiplication
  printf("starting BLOCKED dense matrix multiply \n");
  start = CLOCK();
  for (l=0; l<LOOPS; l++) {
    // Matrix c needs to be reset after each LOOPS iteration.
    //The following overhead is also added to matmul.c and in the sparse multiplication
    //Reset C
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
        c[i][j] = 0.0;
      }
    }

    for(kk=0; kk<N; kk+=B){
      for(jj=0; jj<N; jj+=B){
        for(i=0; i<N; i++){
	 // #pragma omp parallel for shared(c)
          for(j=jj; j<jj+B; j++){
            sum = c[i][j];
            for(k=kk; k<kk+B; k++){  
              sum += a[i][k] * b[k][j]; 
            }
            c[i][j] = sum;
          }
        }
      }
    }
  }
  finish = CLOCK();
  total = finish-start;
  printf("a result %g \n", c[7][8]); 
  printf("The total time for matrix multiplication with dense matrices = %f ms\n\n", total);

  //The following lines of code correspond to the implementation of a parallel matrix multiplication
  printf("starting PARALLEL dense matrix multiply \n");
  pthread_t threads[NTHREADS];
  start = CLOCK();
  for (l=0; l<LOOPS; l++) {
    // Matrix c needs to be reset after each LOOPS iteration.
    //The following overhead is also added to matmul.c and in the sparse multiplication
    //Reset C
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
        c[i][j] = 0.0;
      }
    }

    for(i=0; i<NTHREADS; i++){
      pthread_create(&threads[i], NULL, thread_multi, (void*) i);
    }

    for(i = 0; i < NTHREADS; i++) {
            pthread_join(threads[i], NULL);
        }
    
  }
  finish = CLOCK();
  total = finish-start;
  printf("a result %g \n", c[7][8]); /* prevent dead code elimination */
  printf("The total time for matrix multiplication with dense matrices = %f ms\n\n", total);

  return 0;
}

