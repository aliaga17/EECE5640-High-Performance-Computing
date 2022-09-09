To compile the scripts of homework 3run the following commands. 

Question1:
	module load gcc/10.1.0
	module load openmpi
	mpicc Q1a.c -o Q1a
	sbatch Q1a.script

	mpicc Q1b.c -o Q1b
	sbatch Q1b.script
	
For reading the output:
	more Q1a.out
	more Q1b.out


Question2:
	module load gcc/10.1.0
	module load openmpi
	mpicc Q2a.c -o Q2a
	sbatch Q2a_2nodes.script
	sbatch Q2a_4nodes.script

	mpicc Q2b.c -o Q2b
	sbatch Q2b_2nodes.script
	sbatch Q2b_4nodes.script

For reading the output:
	more Q2a_2nodes.out
	more Q2a_4nodes.out
	more Q2b_2nodes.out
	more Q2b_4nodes.out






