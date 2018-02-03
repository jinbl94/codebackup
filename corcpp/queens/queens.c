#include <stdio.h>
#include <stdlib.h>

int QUEEN_NUM;
int *position;
int *column;
int *up_diag;
int *dn_diag;
int NUM=0;

void place(int i);
void queens();
void usage();

void place(int i){
	int j;

	for(j=0;j<QUEEN_NUM;j++){
		if(column[j]&up_diag[i+j]&dn_diag[i-j+QUEEN_NUM-1]){
			position[i]=j;
			column[j]=up_diag[i+j]=dn_diag[i-j+QUEEN_NUM-1]=0;

			if(i<7) 
				place(i+1);
			else{
				NUM++;
				fprintf(stdout,"%2d:",NUM);
				for(int k=0;k<QUEEN_NUM;k++)
					fprintf(stdout," %d",position[k]);
				fprintf(stdout,"\n");
			}

			column[j]=up_diag[i+j]=dn_diag[i-j+QUEEN_NUM-1]=1;
		}
	}
}

void queens(){
	column=(int *)malloc(sizeof(int)*QUEEN_NUM);
	position=(int *)malloc(sizeof(int)*(QUEEN_NUM));
	up_diag=(int *)malloc(sizeof(int)*(2*QUEEN_NUM-1));
	dn_diag=(int *)malloc(sizeof(int)*(2*QUEEN_NUM-1));

	for(int i=0;i<QUEEN_NUM;i++){
		column[i]=1;
	}

	for(int i=0;i<(2*QUEEN_NUM-1);i++){
		up_diag[i]=dn_diag[i]=1;
	}

	place(0);

	free(column);
	free(position);
	free(up_diag);
	free(dn_diag);
}

int main(int argc,char **argv){
	QUEEN_NUM=8;
	queens();
	return 0;
}
