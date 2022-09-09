#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

// Approximation of the number PI through the Leibniz's series
// Language: C

__global__ void computePi(float *pi, double n){
    //Global thread identifier
    int thread_id = blockIdx.x * blockDim.x + threadIdx.x;

    float i = 2 * thread_id + 1;
    int s = (1-2*(thread_id%2));
    float tmp;

    //Using as many threads as operations, not more
    if(i <= (2 * n)){
        tmp = s * (4 / i);
        atomicAdd(pi, tmp);
    }

}

int main(int argc, char *argv[])
{
    //timing variables
    struct timeval  start, end;
    double comp_time;

    //Start timer
    gettimeofday(&start, NULL);

    double n;// Number of iterations and control variable

    printf("GPU implementation of the approximation of the number PI through the Leibniz's series\n");
    printf("\nEnter the number of iterations: ");    
    scanf("%lf",&n);
    printf("\nPlease wait. Running...\n");    

    float* pi;
    cudaMallocManaged(&pi, sizeof(float));
    *pi = 0.0;

    //Set dimensinos of blocks and grid
    int THREADS = 512;
    int BLOCKS = (n + THREADS - 1) / THREADS;

    computePi<<<BLOCKS, THREADS>>>(pi, n);

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));

    cudaDeviceSynchronize();

    //Stop timer
    gettimeofday(&end, NULL);
    comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec))); 
    printf("\nAproximated value of PI = %1.16lf\n", *pi);
    printf("SINGLE precision total computing time for n=%.0lf: %f\n", n, comp_time);

    cudaFree(pi);

    return 0;
}