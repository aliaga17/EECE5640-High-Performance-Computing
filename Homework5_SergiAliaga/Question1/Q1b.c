//Program to compute an histogram using cuda kernels
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<omp.h>

#define N (1 << 10) 
#define UPPER_LIM 10000000
#define LOWER_LIM  1
#define NBINS 100

/* generate random numbers within the specified limit */
int generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

int main(int argc, char *argv[]){

    //timing variables
    struct timeval  start, end;
    double comp_time;

    //Start timer
    gettimeofday(&start, NULL);

    //Data 
    size_t bytes_data =N * sizeof(int);
    //Bins
    size_t bytes_bins = NBINS * sizeof(int);
    
    //Memory allocation
    int *data;
    int *bins;
    //Auxiliar data structure to print one element of each class
    int *results;
    data = malloc(bytes_data);
    bins = malloc(bytes_bins);
    results = malloc(bytes_bins);
 
    //Initialize data with random numbers
    for (int i = 0; i < N; i ++) {
        data[i] = generate_random_number(LOWER_LIM, UPPER_LIM);
    }
    //Set divisor for finding the corresponding bin for an input, 
    // accounting for bins of irregular size in case UPPER_LIM - LOWER_LIM is not 
    // divisible by NBINS
    int DIV = (UPPER_LIM - LOWER_LIM + NBINS - 1) / NBINS;

    //Initialize bins and result
    for(int i = 0; i<NBINS; i++){
        bins[i] = 0;
        results[i] = 0;
    }

    //Compute histogram
    #pragma omp parallel for 
    for(int i = 0; i<N; i++){
        int bin = (data[i] - LOWER_LIM)/ DIV;
        bins[bin] += 1;
        if(results[bin] == 0) results[bin] = data[i];
    }

    //Stop timer
    gettimeofday(&end, NULL);
    comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec))); 
    printf("Total computing time: %f\n", comp_time);

    printf("Elements of each class of the %d bins:\n", NBINS);
    int tmp = 0;
    for(int i = 0; i<NBINS; i++){
        tmp+=bins[i];
        printf("%d, ", results[i]);
    }
    printf("\nTotal number of elements counted: %d\n", tmp);

    return 0;
}
