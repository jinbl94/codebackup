#! /bin/bash -
# generate iplist range 64.233.160.0~64.233.191.255

file=$1
echo -n '' > $file

start8_15=160
while [ ${start8_15} -lt 192 ]
do
	start0_7=0
	while [ ${start0_7} -lt 256 ]
	do
		echo -ne "64.233."${start8_15}"."${start0_7}"\n" >> $file
		start0_7=`expr $start0_7 + 1`
	done
		start8_15=`expr $start8_15 + 1`
done

exit
