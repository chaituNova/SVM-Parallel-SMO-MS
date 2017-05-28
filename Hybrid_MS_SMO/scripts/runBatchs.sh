#!/bin/bash
#To submit batches to slurm

NARR=(1 2 4 8)
PARR=(1 2 4 8 16 32 64 128)
TARR=(1 2 4 8 16)

#DARR=(0 1 2 3 4 5)
DARR=(1)
NT_LIM=64
PT_LIM=16

for dtst in ${DARR[@]};
do
		for node in ${NARR[@]};
		do
			for proc in ${PARR[@]};
			do
					if [ $proc -lt $node ]
					then
							continue;
					fi
					for trd in ${TARR[@]}
					do
						cval=$((proc/node))
						cval1=$((cval*trd))
						if [ $cval1 -gt $PT_LIM  ]
						then
							continue;
						fi
						echo "dtst:$dtst node:$node proc:$proc trd:$trd"
                    echo "--ntasks=$proc --cpus-per-task=$trd --nodes=$node multi-job-par.sh $dtst $node $proc $trd"
                    sbatch --ntasks=$proc --cpus-per-task=$trd --nodes=$node multi-job-par.sh $dtst $node $proc $trd
					done
			done
		done
done

