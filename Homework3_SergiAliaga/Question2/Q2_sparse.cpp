#include"Eigen/Sparse"
#include <vector>
#include <iostream>
#include <time.h>

#define N 512        
#define LOOPS 10

double a[N][N]; /* input matrix */
double b[N][N]; /* input matrix */
double c[N][N]; /* result matrix */

typedef Eigen::SparseMatrix<double> SpMat;

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main(){
    SpMat Asparse(N, N),  Bsparse(N,N), Csparse(N,N);
    int i,j,k,l, num_zeros;
    double start, finish, total;

    /* initialize a sparse matrix */
    num_zeros = 0; 
    for(i=0; i<N; i++){    
        for(j=0; j<N; j++){
            if ((i<j)&&(i%2>0))
            {
                a[i][j] = (double)(i+j);
                Asparse.insert(i,j) = (double) (i+j);
                b[i][j] = (double)(i-j);
                Bsparse.insert(i,j) = (double) (i-j);

            }
            else
            { 
                num_zeros++;
                a[i][j] = 0.0;
                b[i][j] = 0.0;
            }
            
        }
    }

    printf("starting sparse matrix multiply \n");
    start = CLOCK();
    for (l=0; l<LOOPS; l++) {
        Csparse = (Asparse * Bsparse).pruned();
    }
    finish = CLOCK();
    total = finish-start;
    Eigen::MatrixXd Cdense = Eigen::MatrixXd(Csparse);
    printf("A result %g \n", Cdense(7,8)); /* prevent dead code elimination */
    printf("The total time for matrix multiplication with sparse matrices = %f ms\n", total);
    printf("The sparsity of the a and b matrices = %f \n", (float)num_zeros/(float)(N*N));

}
