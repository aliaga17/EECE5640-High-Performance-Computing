#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>

//Version of Q1a.c but only with the float (SP) and vectorized implementation

#define _USE_MATH_DEFINES
#define NTERMS 1e4

float angles[4] = {10,20,30,40};
double time_float[4];

//Angle in degrees!!
//More efficient version than Q1a.c

float sin_float(float angle){
    float angle_rad = angle * M_PI/180;
    float sum = angle_rad, fact = 1.0, power = angle_rad;
    for(int n=1;n<NTERMS;n++){ 
        power = power * angle_rad * angle_rad;
        fact = fact * (2*n) * (2*n+1);
        sum += (1-2*(n%2)) * power / fact; 
    }
    return sum;
}

double average(double arr[], int size){
    double mean = 0;
    for(int i = 0; i < size;i++){
        mean += arr[i]/size;
    }
    return mean;
}


int main(){
    struct timeval  start, end;
    double avg_float, avg_double;

    printf("Computing sin(x) for x=");
    for(int i = 0; i<4;i++){
        printf("%f, ", angles[i]);
    } 
    printf("degrees\n\n");
    for(int i=0;i<4;i++){
        gettimeofday(&start, NULL);
        float f = sin_float(angles[i]);
        gettimeofday(&end, NULL);
        time_float[i] = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));

        printf("FLOAT Sin(%.1f) = %f\n", angles[i], f);
    }
    avg_float = average(time_float, 4);
    printf("Average computing time FLOAT: %f\n", avg_float);
}