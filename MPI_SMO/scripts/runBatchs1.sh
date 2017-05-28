#!/bin/bash
#To submit batches to slurm

NPARR=(1 2 4 8 16 32 64 128)
#DARR=(0 1 2 3 4 5)
DARR=(6)

for dtst in ${DARR[@]};
do
	for np in ${NPARR[@]};
	do
					echo "dtst:$dtst node:$np proc:$np"
					sbatch --nodes=$np --ntasks=$np multi-job-par.sh $dtst $np $np
	done
done

