#! /bin/bash -
sync
echo 3 > /proc/sys/vm/drop_caches
swapoff /dev/mapper/ubuntu--vg-swap_1
swapon /dev/mapper/ubuntu--vg-swap_1
exit
