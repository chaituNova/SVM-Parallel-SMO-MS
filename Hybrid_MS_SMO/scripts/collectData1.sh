#!/bin/bash
# to collect data from the slurmfiles to txt files to be easily plotted for 3D graph

if [ $# -eq 0 ] || [ $1 -lt 0 ] || [ $1 -gt 5 ]
then
		echo "Please give one correct argument of dataset (0-mnist, 1-splice, 2-not mnist, 3-a9a, 4-ijcnn1, 5-codrna)"
		echo "Also, if necessary give directory path as second argument"
		exit
fi
wdir="."
if [ $# -eq 2 ]
then
  wdir=$2
  echo "Second argument path is taken "
else
  echo "Current directory path is taken "
fi

slrm="$wdir/slurm-*"
dtst=$1
case "$dtst" in 
		0) dname="mnist"
		;;
		1) dname="splice"
		;;
		2) dname="notmnist"
		;;
		3) dname="a9a"
		;;
		4) dname="ijcnn1"
		;;
		5) dname="codrna"
		;;
esac
echo $dname
opdir="${dname}_output"
if [ -d $opdir ]
then
		echo "$opdir alredy exists ! deleting!"
		rm -rf $opdir
fi
mkdir $opdir
opfname="$opdir/$dname"
sslr=`grep -w "dtst:${dtst} node:1 proc:1 trd:1" $slrm -l `
echo $sslr
if [ -z $sslr ]
then
		echo "Serial smo missing, Cannot calculate speedup so get lost !!. I am exting"
		rm -rf $opdir
		exit
fi

stime=`cat $sslr | grep real |awk '{print $2}'|awk -F "m|s" '{print $1*60+$2}'`
echo $stime

nodes=`cat $slrm |grep "dtst:$dtst" |awk '{print $2}' |awk -F ":" '{print $2}' |sort -un`

for node in $nodes
do
	echo "in node: "$node
	opfname_n="${opfname}_n${node}"
	opf_np="${opfname_n}_proc.txt"
	opf_nt="${opfname_n}_thrd.txt"
	opf_ns="${opfname_n}_spdp.txt"
	procs=`cat $slrm |grep -w "dtst:$dtst node:$node" |awk '{print $3}' |awk -F ":" '{print $2}' |sort -un`
	for proc in $procs
	do
		echo "in proc: "$proc
		thrds=`cat $slrm |grep -w "dtst:$dtst node:$node proc:$proc" |awk '{print $4}' |awk -F ":" '{print $2}' |sort -un`
		proc_line=""
		thrd_line=""
		spdp_line=""
		for thrd in $thrds
		do
			echo "in thrd: "$thrd
			proc_line="${proc_line}${proc},"
			thrd_line="${thrd_line}${thrd},"
			sl=`grep -w "dtst:$dtst node:$node proc:$proc trd:$thrd" $slrm -l`
			if [ -z $sl ]
			then
				spdp_line="${spdp_line}0,"
				continue
			fi
			echo "slurm file: "$sl
			pttime=`cat $sl | grep real |awk '{print $2}'|awk -F "m|s" '{print $1*60+$2}'`
			spdp=`echo "scale=2; $stime / $pttime" |bc -l`
			echo "Speedup: "$spdp", parallel time: "$pttime", serial time: "$stime
			spdp_line="${spdp_line}${spdp},"
		done
		echo $proc_line|sed 's/,$//' >> $opf_np
		echo $thrd_line|sed 's/,$//' >> $opf_nt
		echo $spdp_line|sed 's/,$//' >> $opf_ns
	done
done

