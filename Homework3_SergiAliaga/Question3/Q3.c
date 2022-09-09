#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>

#define N 512        
#define LOOPS 10       

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main()
{
  double *A, *B, *C;
  //double a[N][N]; /* input matrix */
  //double b[N][N]; /* input matrix */
  //double c[N][N]; /* result matrix */
  int i,j,k,l, num_zeros;
  double start, finish, total;
  int lda, incx, incy;
  double alpha, beta;

  // Allocating memory for matrices
  A = ( double *)malloc(N*N*sizeof( double ));
  B = ( double *)malloc(N*N*sizeof( double ));
  C = ( double *)malloc(N*N*sizeof( double ));

  CBLAS_LAYOUT Layout;
  CBLAS_TRANSPOSE transa, transb;

  Layout = CblasRowMajor;
  transa = CblasNoTrans;
  transb = CblasNoTrans;

  lda = N;
  incx = 1;
  incy = 1;
  alpha = 1.0;
  beta = 0.0;


  /* initialize a dense matrix */
  for(i=0; i<N; i++){    
    for(j=0; j<N; j++){
      A[i*N+j] = (double)(i+j);
      B[i*N+j] = (double)(i-j);
    }
  }
  
  printf("starting dense matrix multiply \n");
  start = CLOCK();
    cblas_dgemm(Layout, transa, transb, N, N, N, alpha, A, lda, B, N, beta, C, N);
  finish = CLOCK();
  total = finish-start;
  printf("a result %g \n", C[7*N + 8]); /* prevent dead code elimination */
  printf("The total time for matrix multiplication with dense matrices = %f ms\n", total);

  /* initialize a sparse matrix */
  num_zeros = 0; 
  for(i=0; i<N; i++){    
    for(j=0; j<N; j++){
      if ((i<j)&&(i%2>0))
        {
         A[i*N + j] = (double)(i+j);
         B[i*N + j] = (double)(i-j);
        }
      else
        { 
         num_zeros++;
         A[i*N + j] = 0.0;
         B[i*N + j] = 0.0;
        }
       
     }
  }

  printf("starting sparse matrix multiply \n");
  start = CLOCK();
    cblas_dgemm(Layout, transa, transb, N, N, N, alpha, A, lda, B, N, beta, C, N);
  finish = CLOCK();
  total = finish-start;
  printf("A result %g \n", C[7*N + 8]); /* prevent dead code elimination */
  printf("The total time for matrix multiplication with sparse matrices = %f ms\n", total);
  printf("The sparsity of the a and b matrices = %f \n", (float)num_zeros/(float)(N*N));

  return 0;
}

