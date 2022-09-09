//Library includes corresponsing to MassiveThreads and other
#define LENGTH 100
#define NTHREADS 4

float a[LENGTH], b[LENGTH], c[LENGTH];
myth_mutex_t mutex;
myth_thread_t threads[NTHREADS];

void adder(void *arg){
    int id = (int) arg;
    float sum[LENGTH/NTHREADS];
    for(int i = LENGTH/NTHREADS * id; i < LENGTH/NTHREADS * (id+1); i++){
        sum[i - LENGTH/NTHREADS * id] = a[i] + b[i];
    }
    myth_mutex_lock(&mutex);
    for(int i = LENGTH/NTHREADS * id; i < LENGTH/NTHREADS * (id+1); i++){
        c[i] = sum[i - LENGTH/NTHREADS * id];
    }
    myth_mutex_unlock(&mutex);
    
}

int main(int argc, char **argv){
    /* Initialize MassiveThreads */
    myth_init();

    /*Mutex creation*/
    myth_mutex_init(&mutex, NULL);

    /*ULT thread creation*/
    for(int i = 0; i < NTHREADS; i++){
        threads[i] = myth_create(&adder, (void *) i);
    }

    /*ULTs join*/
    for(int i = 0; i < NTHREADS; i++){
        myth_join(thread[i], NULL);
    }

    /*Destroy mutex*/
    myth_mutex_destroy(&mutex)

    /* Finalize MassiveThreads */
    myth_fini();
}


