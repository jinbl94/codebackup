#! /usr/bin/python

import numpy

sequence='10011011000111010100'

def BM(char_sequence):
	bit_sequence=[int(e) for e in char_sequence]
	len_sequence=len(bit_sequence)
	b=numpy.zeros(len_sequence)
	c=numpy.zeros(len_sequence)
	b[0],c[0]=1,1
	l,m,d=0,-1,0
	for n in range(len_sequence):
		sub_bit=bit_sequence[n-l:n+1]
		sub_bit=sub_bit[::-1]
		sub_c=c[0:l+1]
		d=numpy.dot(sub_bit,sub_c)%2
		if d==1:
			temp=c.copy()
			p=numpy.zeros(len_sequence)
			for j in range(l):
				if b[j]==1:
					p[j+n-m]=1
			c=(c+p)%2
			if l <= n/2:
				l=n+1-l
				m=n
				b=temp
			print(n+1,':',c)
	return c,l

c,l=BM(sequence)
print(c,l)
