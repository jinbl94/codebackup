#! /bin/bash -
# ping multiple ips from a text file
# usage: cat iplist | mping 

result="Aviliable IP:";

date
while read addr
do
	ping -c 2 $addr
	if [ $? -eq 0 ];
	then
		result=${result}" "${addr}
	fi
done
echo ${result}

exit 0
