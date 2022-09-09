#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>

#define N_PHILOSOPHERS 6
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define FINISHED 3
#define N_ITERNATIONS 3 //Number of cycles (THINK HUNGRY EAT) per philosopher

//Every time there is a change of state, the table will be printed
//Array indicating the state of each philosopher
int table[N_PHILOSOPHERS];
int froks[N_PHILOSOPHERS];
//Iteration count per philosopher: incremented every change of state
int count[N_PHILOSOPHERS];

pthread_mutex_t mutex;
pthread_cond_t semaphores[N_PHILOSOPHERS];
pthread_t philosophers[N_PHILOSOPHERS];

//The time required for eating and thinking is bounded by the following constants (in seconds)
#define LOWER_BOUND 1
#define UPPER_BOUND 3

//Data structures for computing avg wait time per philospher
//Wait time is the time spent in the hungry state
struct timeval start[N_PHILOSOPHERS], end[N_PHILOSOPHERS];
double wait_time[N_PHILOSOPHERS][N_ITERNATIONS];

#define LEFT (philosopherid+N_PHILOSOPHERS-1)%N_PHILOSOPHERS
#define RIGHT (philosopherid+1)%N_PHILOSOPHERS

//Formating stuff for printing table
void red () {
  printf("\033[1;31m");
}
void green() {
  printf("\033[0;32m");
}
void blue() {
  printf("\033[0;34m");
}
void reset () {
  printf("\033[0m");
}

float random_time();
double average(double arr[], int size);
void think(int philosopherid);
void try_forks(int philosopherid);
void eat(int philosopherid);
void awake_neighbors(int philosopherid);
void* philosopher(void* arg);
void print_table();
void update_state(int philosopherid, int state);

int main(){
    //Initialization
    pthread_mutex_init(&mutex, NULL);
    for(int i=0; i<N_PHILOSOPHERS;i++){
        pthread_cond_init(&semaphores[i], NULL);
    }
    printf("DINNER BEGINS, INITIAL TABLE:\n");
    print_table();
    
    //Thread creation
    for(int i=0; i<N_PHILOSOPHERS;i++){
        pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
    }

    //Thread synchronisation
    for(int i=0; i<N_PHILOSOPHERS;i++){
        pthread_join(philosophers[i], NULL);
    }

    //Clean up and exit
    pthread_mutex_destroy(&mutex);
    for(int i=0; i<N_PHILOSOPHERS;i++){
        pthread_cond_destroy(&semaphores[i]);
    }
    printf("DINNER IS OVER;\n");
    //Compute and print stats (avg. wait time, or avg. wait time per philosopher)
    //Avg. wait time
    double avg_wait_time=0.0;
    for(int i = 0; i< N_PHILOSOPHERS; i++){
        avg_wait_time += average(wait_time[i], sizeof( wait_time[i]) / sizeof(wait_time[i][0]))/N_PHILOSOPHERS;
    }
    printf("Philosophers average wait time:%f\n", avg_wait_time);
    /*
    //Avg. wait time per philosopher
    printf("Philosophers average wait time (1-->%d):\n", N_PHILOSOPHERS);
    for(int i = 0; i< N_PHILOSOPHERS; i++){
        printf("%f\n", average(wait_time[i], sizeof( wait_time[i]) / sizeof(wait_time[i][0])));
    }*/
    pthread_exit(NULL);
    
}

float random_time(){
    float time = ((float)rand()/(float)(RAND_MAX)) * (UPPER_BOUND-LOWER_BOUND) + LOWER_BOUND;
    return time;
}

void think(int philosopherid){
    float time = random_time();
    //printf("Philosopher %d is thinking for %f seconds\n", philosopherid, time);
    sleep(time);
}

void try_forks(int philosopherid){
    pthread_mutex_lock(&mutex);
    update_state(philosopherid, HUNGRY);
    //Start counting wait time
    gettimeofday(&start[philosopherid], NULL);
    //**** Now we acquire forks in this order: 1-RIGHT, 2-LEFT
    while(table[RIGHT] == EATING || table[LEFT]==EATING){
        //**** Try to get right fork, if not, wait
        while(table[RIGHT] == EATING){
            pthread_cond_wait(&semaphores[philosopherid], &mutex);
        }
        //****Grab Right fork
        //****If left fork not available, leave right fork and wait
        if(table[LEFT]==EATING){
            pthread_cond_wait(&semaphores[philosopherid], &mutex);
        }
        //**** Reevaluate if right fork is free and start eating if it is (all wait()s will be skiped)
    }
    //End counting time
    gettimeofday(&end[philosopherid], NULL);
    update_state(philosopherid, EATING);
    // Append elapsed time in the corresponding philosopher and iteration
    wait_time[philosopherid][count[philosopherid]] = ((double) ((double) (end[philosopherid].tv_usec - start[philosopherid].tv_usec) / 1000000 +
                                (double) (end[philosopherid].tv_sec - start[philosopherid].tv_sec)));
    pthread_mutex_unlock(&mutex);
}

void eat(int philosopherid){
    float time = random_time();
    //printf("Philosopher %d is eating for %f seconds\n", philosopherid, time);
    sleep(time);

}

void awake_neighbors(int philosopherid){
    pthread_mutex_lock(&mutex);
    update_state(philosopherid, THINKING);
    if(table[LEFT]==HUNGRY){
        pthread_cond_signal(&semaphores[LEFT]);
    }
    if(table[RIGHT]==HUNGRY){
        pthread_cond_signal(&semaphores[RIGHT]);
    }
    pthread_mutex_unlock(&mutex);
}

//Function to update the state of a philosopher, print table and keep track of count
void update_state(int philosopherid, int state){
    table[philosopherid] = state;
    print_table();
}

void* philosopher(void* arg){
    int philosopherid = (long)arg;
    while(count[philosopherid]<N_ITERNATIONS){
        think(philosopherid);
        try_forks(philosopherid);
        eat(philosopherid);
        awake_neighbors(philosopherid);
        count[philosopherid]++;
    }
    printf("Philospher %d finishes eating and leaves the table\n\n", philosopherid);
    pthread_mutex_lock(&mutex);
    update_state(philosopherid, FINISHED);
    pthread_mutex_unlock(&mutex);
}

void print_table(){
    int ocurrences[3] = {0,0,0};
    //Uncomment if used outside mutex
    //pthread_mutex_lock(&mutex); 
    printf("*****TABLE*****\n[");
    for(int i=0; i<3; i++){
        for(int j=0;j<N_PHILOSOPHERS;j++){
            if(table[j]==i){
                ocurrences[i]++;
            }
            if(i==0){
                //Comment if table to large
                switch (table[j])
                {
                case THINKING:
                    green();
                    printf("THINKING ");
                    reset();
                    printf(", ");
                    break;
                case HUNGRY:
                    blue();
                    printf("HUNGRY");
                    reset();
                    printf(", ");
                    break; 
                case EATING:
                    red();
                    printf("EATING");
                    reset();
                    printf(", ");
                    break; 
                case FINISHED:
                    printf("-------");
                    printf(", ");
                    break; 
                }
            }
        }
    }
    printf("]\n");
    printf("Thinking\tHungry\t\tEating\t\tTotal\n");
    printf("%d\t\t%d\t\t%d\t\t%d\n\n",ocurrences[0], ocurrences[1], ocurrences[2], N_PHILOSOPHERS);
    //pthread_mutex_unlock(&mutex);
}

double average(double arr[], int size){
    double mean = 0;
    for(int i = 0; i < size;i++){
        mean += arr[i]/size;
    }
    return mean;
}
