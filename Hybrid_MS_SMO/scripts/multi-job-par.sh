#!/bin/bash
#SBATCH --mem-per-cpu=7168
#SBATCH -t 00:10:00

CPATH=`pwd`
SMO=$CPATH/smo

dtst=$1
node=$2
proc=$3
trd=$4

#module unload intel
module load openmpi

echo "dtst:$dtst node:$node proc:$proc trd:$trd"
echo "SMO path: $SMO"
time mpirun -np $proc $SMO $dtst $trd 
