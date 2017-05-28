#!/bin/bash
#SBATCH --mem-per-cpu=7168
#SBATCH -t 00:03:00

CPATH=`pwd`
SMO=$CPATH/../smo

dtst=$1
node=$2
proc=$3

#module unload intel
module load openmpi

echo "dtst:$dtst node:$node proc:$proc"
time mpirun -np $proc $SMO $dtst 

