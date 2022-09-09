#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define n 32

__global__ void stencil(float *a, float *b, long N){
    //Global thread identifier
    int thread_id = blockIdx.x * blockDim.x + threadIdx.x;
    //Weird indexing to get the correct mapping between thread id and i, j, k
    int element_idx = (thread_id / 6);
    int i = element_idx % (n-2) + 1;
    int j = (element_idx - i + 1) / (n-2) % (n-2) + 1;
    int k = ((element_idx - i + 1) / (n-2) - j + 1) / (n-2) % (n-2) + 1;
    float tmp;

    //Using as many threads as operations, not more
    if(thread_id < N){
        switch(thread_id % 6){
            case 0:
                tmp = 0.8 * b[k * n * n + j * n + (i - 1)];
                atomicAdd(&a[k * n * n + j * n + i], tmp);
                break;
            case 1:
                tmp = 0.8 * b[k * n * n + j * n + (i + 1)];
                atomicAdd(&a[k * n * n + j * n + i], tmp);
                break;
            case 2:
                tmp = 0.8 * b[k * n * n + (j - 1) * n + i];
                atomicAdd(&a[k * n * n + j * n + i], tmp);
                break;
            case 3:
                tmp = 0.8 * b[k * n * n + (j + 1) * n + i];
                atomicAdd(&a[k * n * n + j * n + i], tmp);
                break;
            case 4:
                tmp = 0.8 * b[(k - 1) * n * n + j * n + i];
                atomicAdd(&a[k * n * n + j * n + i], tmp);
                break;
            case 5:
                tmp = 0.8 * b[(k + 1) * n * n + j * n + i];
                atomicAdd(&a[k * n * n + j * n + i], tmp);
                break;
        }
    }

}

int main(int argc, char *argv[])
{
    //timing variables
    struct timeval  start, end;
    double comp_time;

    //Start timer
    gettimeofday(&start, NULL);

    //Memory allocation
    float* a;
    float* b;
    size_t bytes = (n * n * n) * sizeof(float);
    cudaMallocManaged(&a, bytes);
    cudaMallocManaged(&b, bytes);

    //Initialize b
    for (int i=0; i<(n * n * n); i++) b[i] = 1;

    //Set dimensinos of blocks and grid
    long N = (n-2) * (n-2) * (n-2) * 6; //Total number of operations for the 6-point 3d stencil
    int THREADS = 512;
    int BLOCKS = (N + THREADS - 1) / THREADS;

    stencil<<<BLOCKS, THREADS>>>(a, b, N);

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));

    cudaDeviceSynchronize();

    //Stop timer
    gettimeofday(&end, NULL);
    comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec))); 
    printf("Total computing time for n=%d: %f\n",n, comp_time);
    printf("Total number of threads = %d\n", N);

    //Testing for small n
    /*printf("RESULTS a:\n");
    for (int k=0; k<n; k++){
        for (int j=0; j<n; j++){
            for (int i=0; i<n; i++) {
                printf("%.1f  ", a[k * n * n + j * n + i]);
            }
            printf("\n");
        }
        printf("\n");
    }*/

    cudaFree(a);
    cudaFree(b);

    return 0;
}
