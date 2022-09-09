To compile the scripts of homework 3run the following commands. 

Question1:
gcc Q1a.c -o Q1a
gcc Q1a_eff.c -o Q1a_eff
gcc Q1b.c -o Q1b

Question2:
Gcc verision 10.1.0 required, before compiling run "module load gcc/10.1.0"
For Q2_sparse.cpp the Eigen library is required. Copy the folder "Eigen" to the working directory before compiling.

gcc Q2.c -o Q2 -lpthread
g++ Q2_sparse.cpp -o Q2 

Question3:
Run first "module load openbkas/0.3.6"

gcc Q3.c -o Q3 -lopenblas
