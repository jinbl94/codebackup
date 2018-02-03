#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#define ROUND 5
#define MAX 0x10000

const static int sub[4]={ 0xf, 0xf0, 0xf00, 0xf000 };

const static int s_box[16]={
	0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0x3,
	0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb
};

const static int p_table[16]={
	0x0, 0x4, 0x8, 0xc, 0x1, 0x5, 0x9, 0xd,
	0x2, 0x6, 0xa, 0xe, 0x3, 0x7, 0xb, 0xf
};

/*
integer: the integer you want to transform
bit_array: array used to store the result
length: length of bit_array
require: none
 */
void int_to_bit(int integer, bool *bit_array, int length){
	for(int i=0; i<length; i++){
		bit_array[i]=(integer>>i) & 1;
	}
}

/*
bit_array: the array you want to transform
integer: integer to save the result
length: length of bit_array
require: none
 */
void bit_to_int(bool *bit_array, int &integer, int length){
	integer=0;
	for(int i=0; i<length; i++){
		integer|=bit_array[i]<<i;
	}
}

/*
bit_array: the array you want to transform
length: length of the array
require: none
 */
void S(bool *bit_array, int length){
	for(int i=0; i<length; i+=4){
		int temp=0;
		for(int j=0; j<4; j++){
			temp+=bit_array[i+j]<<j;
		}
		temp=s_box[temp];
		for(int j=0; j<4; j++){
			bit_array[i+j]=(temp>>j)&1;
		}
	}
}

/*
bit_array: the array you want to transform
length: length of the array
require: none
 */
void P(bool *bit_array, int length){
	bool temp_array[16];
	for(int i=0; i<length; i++){
		temp_array[i]=bit_array[p_table[i]];
	}
	for(int i=0; i<length; i++){
		bit_array[i]=temp_array[i];
	}
}

/*
bit_des: array a, as one of the operator numbers and result
bit_sor: array you want to add to bit_des
length: length of both array
require: bit_des and bit_sor with the same length
 */
void XOR(bool *bit_des, bool *bit_sor, int length){
	for(int i=0;i<length;i++){
		bit_des[i]^=bit_sor[i];
	}
}

/*
input: the number you want to encrypt
output: integer to storage the result
key: round keys
require: none
 */
void toy_cipher(int input, int &output, bool *key){
	static bool bit_input[16];
	int_to_bit(input, bit_input, 16);
	//first xor operation
	//XOR(bit_input, key[0], 16);
	for(int i=0; i<ROUND; i++){
		S(bit_input, 16);
		P(bit_input, 16);
		//xor operation with round key
		//XOR(bit_input, key[i+1], 16);
	}
	bit_to_int(bit_input, output, 16);
}

int main(){
	int cipher_array[MAX];
	//secret key
	static bool key[16];
	
	fprintf(stdout,"Encrypting...\n");
	for(int i=0;i<MAX;i++){
		toy_cipher(i, cipher_array[i], key);
	}
	fprintf(stdout,"Compeleted\n");
	int n=0x1a3d;
	fprintf(stdout,"The cipher of %x is %x\n", n, cipher_array[n]);
	return 0;
}
