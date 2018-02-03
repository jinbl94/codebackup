#! /bin/bash -
#function usage(){
#	echo "this is a tet!"
#}
#
#echo $#": "$@
#
#file=$1
#echo "" > $file
#
#start8_15=160
#while [ ${start8_15} -lt 192 ]
#do
#	start0_7=0
#	while [ ${start0_7} -lt 256 ]
#	do
#		echo " 64.233."${start8_15}"."${start0_7} >> $file
#		start0_7=`expr $start0_7 + 1`
#	done
#		start8_15=`expr $start8_15 + 1`
#done
#
#exit
if [ ! -d ./test ]
then
	echo "file don't exists"
fi
