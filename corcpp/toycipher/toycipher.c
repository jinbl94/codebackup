#include <stdio.h>
#include <stdlib.h>

#define ROUND 5
#define MAX 0x10000

const static int s_box[16]={
	0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe,
	0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb
};

const static int p_table[16]={
	0x0, 0x4, 0x8, 0xc, 0x1, 0x5, 0x9, 0xd,
	0x2, 0x6, 0xa, 0xe, 0x3, 0x7, 0xb, 0xf
};

const static void int_to_bit(int integer, bool *bit_array, int length){
	for(int i=0; i<length; i++){
		bit_array[i]=(integer>>i) & 1;
	}
}

const static void bit_to_int(bool *bit_array, int &integer, int length){
	integer=0;
	for(int i=0; i<length; i++){
		integer|=bit_array[i]<<i;
	}
}

const static void S(bool *bit_array, int length){
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

const static void P(bool *bit_array, int length){
	bool temp_array[16];
	for(int i=0; i<length; i++){
		temp_array[i]=bit_array[p_table[i]];
	}
	for(int i=0; i<length; i++){
		bit_array[i]=temp_array[i];
	}
}

void XOR(bool *bit_des, bool *bit_sor, int length){
	for(int i=0;i<length;i++){
		bit_des[i]^=bit_sor[i];
	}
}

const static void toy_cipher(int input, int &output, bool *key){
	static bool bit_input[16];
	int_to_bit(input, bit_input, 16);
	//XOR(bit_input, key, 16);
	for(int i=0; i<(ROUND-1); i++){
		S(bit_input, 16);
		P(bit_input, 16);
		//XOR(bit_input, key, 16);
	}
	//S(bit_input, 16);
	bit_to_int(bit_input, output, 16);
}

int main(){
	static int cipher_array[MAX];
	static int counter_array[MAX];
	static bool flag_array[MAX];
	static int input_diff[2], output_diff[2], max_diff[2]={0x0, 0x0},index=0;
	static bool *key;

	//Encrypt
	for(int i=0;i<MAX;i++){
		toy_cipher(i, cipher_array[i], key);
	}
	for(int i=0x1;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			counter_array[j]=0;
			flag_array[j]=false;
		}
		for(int j=0;j<MAX;j++){
			if(flag_array[j]){
				continue;
			}else{
				index=cipher_array[j]^cipher_array[j^i];
				counter_array[index]+=1;
				flag_array[j]=true;
				flag_array[j^i]=true;
			}
		}
		for(int j=0;j<MAX;j++){
			if(counter_array[j]>max_diff[0]){
				input_diff[1]=input_diff[0];
				output_diff[1]=output_diff[0];
				max_diff[1]=max_diff[0];
				input_diff[0]=i;
				output_diff[0]=j;
				max_diff[0]=counter_array[j];
			}
		}
	}
	fprintf(stdout, "input_diff=%x, output_diff=%x, number=%x, percent=%f\n",input_diff[0],output_diff[0],max_diff[0],((float)max_diff[0])/0x8000);
	fprintf(stdout, "input_diff=%x, output_diff=%x, number=%x, percent=%f\n",input_diff[1],output_diff[1],max_diff[1],((float)max_diff[1])/0x8000);
	return 0;
}
