#!/bin/bash
# This script is to read the relevant contents of the slurm files generated
wdir="."
if [ $# -ne 0 ]
then
	wdir=$1
	echo "First argument path is taken "
	echo "output:"
	echo ""

else
	echo "Current directory path is taken "
	echo "output:"
	echo ""
fi

slist=`ls $wdir/slurm-*`

for sl in $slist
do
		cat $sl | grep dtst
		cat $sl | grep real
done
