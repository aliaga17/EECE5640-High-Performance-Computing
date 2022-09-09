#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>
#include <sys/time.h>
#include<time.h>

#define NTHREADS 32
#define NDARTS 320000000
#define PI 3.14159265359
#define NDARTS_SERIAL 10000000

// We implement the solution by generating random points in a 2D Cartesian coordinate system,
// where x is the horitzontal component and y the vertical one
//We compute the distance to the center of the plane d^2=x^2+y^2
// If the point falls inside the circle, we add 1 to in_circle.
// Finally, we divide in_circle by the total number of darts
//Reference pi value to compute the error: 3.14159265359

int thread_in_circle = 0;
int darts_per_thread = NDARTS/NTHREADS;
pthread_mutex_t mutex;
pthread_t workers[NTHREADS];

double random_float();
float single_thread();
void* worker(void* arg);
float multi_thread();

int main(){
    double single_thread_performance = single_thread();
    double multi_thread_performance = multi_thread();

    printf("Speedup = %f\n\n", single_thread_performance/multi_thread_performance);
}

double random_float(int* seed){
    double n = ((double) rand_r(seed)/(double) (RAND_MAX));
    return n;
}

float single_thread(){
    struct timeval  start, end;
    double comp_time, pi, x, y, distance;
    gettimeofday(&start, NULL);
    int in_circle=0;
    int i, seed;
    srand(time(0));
    for(i=0;i<NDARTS_SERIAL;i++){
        x =random_float(&seed);
	    y =random_float(&seed);
        distance = sqrt(x*x+y*y);
        //Comparing with 1.0 because if compared with 1 does not give enough precision
        if (distance<=1.0){
            in_circle++;
        }
    }
    pi = (double) in_circle / (double) NDARTS * 4;
    gettimeofday(&end, NULL);
    comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));
    printf("\nNumber of darts:%d \n1 Thread computing time: %fs \nObtained value pi= %f \nError is %f\n\n", NDARTS, comp_time, pi, fabs(pi-PI));
    return comp_time;
    
}

void* worker(void* arg){
    int in_circle=0;
    int i, seed;
    double x, y, distance;
    for(i=0;i<darts_per_thread;i++){
        x =random_float(&seed);
	    y =random_float(&seed);
        distance = sqrt(x*x+y*y);
        if (distance<=1.0){
            in_circle++;
        }
    }
    pthread_mutex_lock(&mutex);
    thread_in_circle += in_circle;
    pthread_mutex_unlock(&mutex);
}

float multi_thread(){
    struct timeval  start, end;
    double comp_time;
    gettimeofday(&start, NULL);
    double pi;
    int i;
    for(i=0; i<NTHREADS;i++){
        pthread_create(&workers[i], NULL, worker, NULL);
    }
    for(i=0; i<NTHREADS;i++){
        pthread_join(workers[i], NULL);
    }
    pi = (double) thread_in_circle / (double) NDARTS * 4;
    gettimeofday(&end, NULL);
    comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));
    printf("%d Threads computing time: %fs \nObtained value pi= %f \nError is %f\n\n", NTHREADS, comp_time, pi, fabs(pi-PI));
    return comp_time;
}
