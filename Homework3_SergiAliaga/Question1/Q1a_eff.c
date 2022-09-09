#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<math.h>

#define _USE_MATH_DEFINES
#define NTERMS 1e8

float angles[4] = {10,20,30,40};
double time_float[4], time_double[4];

//Angle in degrees!!
//More efficient version than Q1a.c

float sin_float(float angle){
    float angle_rad = angle * M_PI/180;
    float sum = 0.0, fact = 1.0, power = 1.0;
    for(int n=0;n<NTERMS;n++){ 
        power = power * angle_rad * angle_rad;
        if(n>0) fact = fact * (2*n) * (2*n+1);
        sum += (1-2*(n%2)) * power / fact; 
    }
    return sum;
}


double sin_double(double angle){
    double angle_rad = angle * M_PI/180;
    double sum = 0.0, fact = 1.0, power = 1.0;
    for(int n=0;n<NTERMS;n++){
        power = power * angle_rad * angle_rad;
        if(n>0) fact = fact * (2*n) * (2*n+1);
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

        gettimeofday(&start, NULL);
        double d = sin_double((double) angles[i]);
        gettimeofday(&end, NULL);
        time_double[i] = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));
        
        printf("FLOAT Sin(%.1f) = %f\n", angles[i], f);
        printf("DOUBLE Sin(%.1f) = %f\n", angles[i], d);
        printf("Difference: %f\n\n", fabs(d-f));
    }
    avg_float = average(time_float, 4);
    avg_double = average(time_double, 4);
    printf("Average computing time FLOAT: %f\n", avg_float);
    printf("Average computing time DOUBLE: %f\n", avg_double);
    printf("Computing time difference: %f\n\n", avg_double-avg_float);
}