#!/usr/bin/python

RED='\x1b[31;40m'
REDEND='\x1b[0m'

cipher=''
lettermap=dict()
freq=dict()

for i in range(26):
	lettermap[chr(ord('A')+i)]=chr(ord('A')+i)
	freq[chr(ord('A')+i)]=0

def show(line):
	for e in line:
		if e==lettermap[e]:
			print(e,end='')
		else:
			print(RED+lettermap[e]+REDEND,end='')
	print(' ',end='')
