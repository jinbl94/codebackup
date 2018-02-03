#include<iostream>

using namespace std;

int main(){
	int n=10;
	for(int i=1;i<n;i++){
		for(int k=1;k<n-i;k++){
			cout<<' ';
		}
		int j=1;
		for(;j<i;j++){
			cout<<j;
		}
		for(;j>0;j--){
			cout<<j;
		}
		cout<<endl;
	}

	return 0;
}
