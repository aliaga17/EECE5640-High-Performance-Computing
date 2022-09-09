To compile the scripts of homework 5 run the following commands on a node with a GPU: 

To request interactive node with a GPU run: 

srun -p reservation --reservation=EECE5640 -N 1 -n 1 --gres=gpu:1 --pty /bin/bash

Question1:
	module load gcc/6.4.0
	module load cuda/10.2

	nvcc Q1a.cu -o Q1a
	gcc Q1b.c -o Q1b -fopenmp
	
Question2:
	module load gcc/6.4.0
	module load cuda/10.2

	nvcc Q2a.cu -o Q2a

Question4:
	module load gcc/6.4.0
	module load cuda/10.2

	nvcc Q4.c -o Q4 -arch=sm_61
	nvcc Q4_single.c -o Q4_single		







