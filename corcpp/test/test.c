#include <stdio.h>

void show(int number){
	number=100;
	fprintf(stdout,"%d\n",number);
}

void int_to_bit(int integer, bool *bit_array, int length){
	for(int i=0;i<length;i++){
		bit_array[i]=(integer>>i)&1;
	}
}

void bit_to_int(bool *bit_array, int &integer, int length){
	integer=0;
	for(int i=0;i<length;i++){
		integer|=bit_array[i]<<i;
	}
}

int main(){
	int a=10,b=0;
	static bool bit_a[8];
	int_to_bit(a,bit_a,8);
	for(int i=0;i<8;i++){
		fprintf(stdout,"%d ",bit_a[i]);
	}
	bit_to_int(bit_a,b,8);
	fprintf(stdout,"\n%d\n",b);
	return 0;
}
