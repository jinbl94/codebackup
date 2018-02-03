#!/bin/bash -
echo encrypting claude
./encrypt claude claude.enc
echo anylysing claude.enc
./anylyse claude.enc claude.enc.any
exit
