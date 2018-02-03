#! /usr/bin/python
import sys
import zipfile

RED='\x1b[31;40m'
REDEND='\x1b[0m'

##compute the length of key##
def kasiski(cipher):
	input_str='3'
	while True:
		input_str=input(RED+'Patern'+REDEND+' Length: ')
		try:
			step=int(input_str)
		except ValueError:
			print('Not Integer')
			break
		patern=dict()
		
		for i in range(len(cipher)):
			if i+step<len(cipher):
				if cipher[i:i+step] in patern.keys():
					patern[cipher[i:i+step]]+=1
				else:
					patern[cipher[i:i+step]]=1
			else:
				break
		
		key_list=list(patern.keys())
		
		for e in key_list:
			if patern[e]==1:
				patern.pop(e)
		
		print('Distance between paterns:')
		patern_num=0
		line_end=''
		for e in patern.keys():
			patern_num+=1
			distance=[]
			position=0
			first=True
			for i in range(len(cipher)-step):
				if cipher[i:i+step]==e:
					if first:
						first=False
						position=i
						continue
					distance.append(i-position)
			if len(distance)>3:patern_num-=1
			if patern_num%4==0:
				line_end='\n'
			else:
				line_end='  '
			print(e+': ',end='')
			for i in distance:
				print('{0:<3d}'.format(i),end=' ')
				##print('{0:3d}/6={1:3.2f}'.format(i,i/6),end=' ')
			print('',end=line_end)
		print('\n'+RED+'***********divide line***********'+REDEND)

##decrypt##
def MI(x,y):
	assert len(x)==len(y)
	result=0
	for i in range(len(x)):
		result+=x[i]*y[i]
	return result

def reverse(n,mod):
	for i in range(mod):
		if (n*i)%mod==1:
			return i

def find_key(line):
	nature=[0.08167,0.01492,0.02782,0.04253,0.12705,0.02228,0.02015,0.06094,0.06996,0.00153,0.00772,0.04025,0.02406,0.06749,0.07507,0.01929,0.0009,0.05987,0.06327,0.09056,0.02758,0.00978,0.02360,0.0015,0.01974,0.00074]
	a_list=[1,3,5,7,9,11,15,17,19,21,23,25]

	ai=0
	ki=0
	min_dist=1
	for a in a_list:
		freq=[]
		mi_list=[]
		for i in range(26):
			freq.append(line.count(chr(ord('A')+(a*i)%26),0,len(line))/len(line))
		for i in range(26):
			mi_list.append(MI(freq[i:]+freq[:i],nature))
		for i in range(len(mi_list)):
			if abs(mi_list[i]-0.065546)<min_dist:
				min_dist=abs(mi_list[i]-0.065546)
				ai=a
				ki=i
	return ai,ki

def find_keyword(cipher,n):
	k=[]
	a=[]
	cipher_rearanged=[]
	for i in range(n):
		cipher_rearanged.append(cipher[i::n])
	for i in range(len(cipher_rearanged)):
		ai,ki=find_key(cipher_rearanged[i])
		a.append(ai)
		k.append(ki)
	return a,k

def decrypt(cipher,key):
	plaintext=''
	for i in range(len(cipher)):
		plaintext+=chr(ord('a')+(ord(cipher[i])-ord(key[i%len(key)]))%26)
	print(RED+plaintext+REDEND)

def decrypt_new(cipher,a,k):
	plaintext=''
	mod1=len(a)
	mod2=len(k)
	for i in range(len(cipher)):
		plaintext+=chr(ord('a')+(((ord(cipher[i])-ord('A'))*reverse(a[i%mod1],26)-k[i%mod2])%26))
	print(RED+plaintext+REDEND)

def input_keylen():
	input_word=input(RED+'Key'+REDEND+' Length: ')
	if input_word=='quit':
		sys.exit()
	else:
		return int(input_word)

def read_from_zip(filename1,filename2):
	myzipfile=zipfile.ZipFile(filename1,'r')
	return myzipfile.open(filename2,'r').read().decode('utf-8').upper()

## this part is written to solve the problem of 'Applied Cryptogrhpy' class.
##kasiski(cipher)
##key_len=input_keylen()
##key_word=find_keyword(cipher,key_len)
##print('Key: '+RED+key_word+REDEND)
##decrypt(cipher,key_word)

##cihper_num should be your cihper index. unzip the archive of all cipher texts, and rename it into 'ciphers.zip'. otherwise change 'ciphers.zip' into the name of your archive file.
cipher_num='6'
cipher_txt='cipher/cihper'+cipher_num+'.txt'
cipher=read_from_zip('ciphers.zip',cipher_txt)
print(cipher)
## you can select the length of patern in function kasiski.
kasiski(cipher)
## the length of cipher should be the LCM of all patern distances. it's 5 in my cipher. once the length of key is determined, you can leave all stuffs to this program.
a,k=find_keyword(cipher,5)
decrypt_new(cipher,a,k)
